#include<iostream>
#include<chrono>

#include "sensor_node.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/clock.hpp"
#include "std_msgs/msg/header.hpp"
#include "tdk_robokit_interface/msg/range_data.hpp"

using namespace std::chrono;
using std::hex;
using std::dec;

static void publish_message();

extern "C" {
int serial_data_parser(void);
int handle_asic_sensor(int);
}

// Globals
uint32_t range_mm = 0;
uint8_t rx_sensor_id = 100, tx_sensor_id = 100;

/**
 * @brief Helper function to convert degree to radian
 * 
 * @param data 
 */
float convert_degree(float degree)
{
    float pi = 3.14159265359;
    return (degree * (pi / 180));
}

/**
 * @brief Callback handler to update GRV data.
 *      
 *        Also publishes the IMU & GRV data to ROS topic.
 * 
 * @param data 
 */

void chirp_data_cmd_handler(uint8_t *data){

    rx_sensor_id = (uint8_t) *(data);
    tx_sensor_id = (uint8_t) *(data+1);

    data = data + 15; // Skip other offsets

    uint32_t range_cm = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);

    range_cm = range_cm / 32;
    range_mm = range_cm / 10;

    // std::cout << "range_mm: " << range_mm << std::endl;

    /**
     * Publish CHIRP message on receiving the data.
     */
    if(rx_sensor_id == tx_sensor_id)
        publish_message();
}

/**
 * @brief CH101 ROS2 Publisher for publishing IMU & GRV data 
 * 
 */
class CH101_Publisher : public rclcpp::Node
{
public:
    CH101_Publisher() : Node("tdk_robokit_ch101")
    {
        // Create a Publisher
        CH101_publisher_ = this->create_publisher<tdk_robokit_interface::msg::RangeData>("tdk_robokit_ch101", 10);
        RCLCPP_INFO(this->get_logger(), "Initiating CHIRP Publisher");

        // Access tdk_robokit_driver to open serial comm to RBK
        serial_openned = serial_data_parser();

        if(!serial_openned)
        {
            RCLCPP_INFO(this->get_logger(), "Serial openned successfully");
            RCLCPP_INFO(this->get_logger(), "Enabling Chirp Sensor in RBK");
            handle_asic_sensor(1);
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Serial opening failed... ");
        }
    }

    friend void publish_message();

private:

    int serial_openned;

    // timer declaration
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<tdk_robokit_interface::msg::RangeData>::SharedPtr CH101_publisher_;
    rclcpp::Clock::SharedPtr clock = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);

    
    /**
     * @brief Publish message to ROS2 topic
     * 
     */
    void chirp_data_publisher(){
        auto ch_msg = tdk_robokit_interface::msg::RangeData();
        auto ch_header = std_msgs::msg::Header();

        ch_header.stamp = clock->now();
        ch_header.frame_id = "tdk_robokit_ch101";
        ch_msg.header = ch_header;

        ch_msg.radiation_type = ch_msg.ULTRASOUND;
        ch_msg.field_of_view = convert_degree(180.0);
        ch_msg.min_range = 0.04;
        ch_msg.max_range = 1.2;
        ch_msg.range = (float) range_mm / 100;
        ch_msg.sensor_id = rx_sensor_id;

        // Publish imu_msg
        CH101_publisher_->publish(ch_msg);
    }

};

// Global shared_ptr used for accessing publisher node
std::shared_ptr<CH101_Publisher> common_node(nullptr);


/**
 * @brief A friend function to CH101_Publisher that helps publishing IMU & GRV messages.
  * 
 * @return: void 
 */
static void publish_message(){
    common_node->chirp_data_publisher();
}

/**
 * @brief Main driver function that initiates the IMU Publisher and RCL lib
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto CH101_publisher_node = std::make_shared<CH101_Publisher>();
    common_node = CH101_publisher_node;
    rclcpp::spin(CH101_publisher_node);
    rclcpp::shutdown();
    return 0;
}