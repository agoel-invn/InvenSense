#include<iostream>
#include<chrono>

#include "sensor_node.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/clock.hpp"
#include "std_msgs/msg/header.hpp"
#include "tdk_robokit_interface/msg/pressure.hpp"

using namespace std::chrono;
using std::hex;
using std::dec;

static void publish_message();

extern "C" {
int serial_data_parser(void);
int handle_pres_sensor(int);
}

// Globals
float pressure_mb = 0.0;
float celsius = 0.0;
float height_m = 0.0;

typedef union {
 
    float f;
    struct
    {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
 
    } raw;
} getFloatUnion;

getFloatUnion getf;

float getFloat (uint32_t val){
    uint32_t man = val & 0x007FFFFF;
    uint32_t exp = (val & 0x7F800000) >> 23;
    uint32_t sign = (val & 0x80000000) >> 31;

    getf.raw.mantissa = man;
    getf.raw.exponent = exp;
    getf.raw.sign = sign;

    return getf.f;
}

/**
 * @brief Callback handler to update PRES data.
 *      
 *        Also publishes the PRES data to ROS topic.
 * 
 * @param data 
 */

void pres_data_cmd_handler(uint8_t *data){

    data = data + 8; // Skip timetag_us
    
    uint32_t data_ = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    pressure_mb = getFloat(data_);
    data = data + 4;

    data_ = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    celsius = getFloat(data_);
    data = data + 4;

    data_ = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    height_m = getFloat(data_);


    /**
     * Publish message on receiving the PRES data.
     */
    publish_message();
}

/**
 * @brief ICP10101 ROS2 Publisher for publishing PRES data 
 * 
 */
class ICP10101_Publisher : public rclcpp::Node
{
public:
    ICP10101_Publisher() : Node("tdk_robokit_icp10101")
    {
        // Create a Publisher
        ICP10101_publisher_ = this->create_publisher<tdk_robokit_interface::msg::Pressure>("tdk_robokit_icp10101", 10);
        RCLCPP_INFO(this->get_logger(), "Initiating PRES Publisher");

        // Access tdk_robokit_driver to open serial comm to RBK
        serial_opened = serial_data_parser();

        if(!serial_opened)
        {
            RCLCPP_INFO(this->get_logger(), "Serial opened successfully");
            RCLCPP_INFO(this->get_logger(), "Enabling Pres Sensor in RBK");
            handle_pres_sensor(1);
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Serial opening failed... ");
        }

    }

    friend void publish_message();

private:

    int serial_opened;
    rclcpp::Publisher<tdk_robokit_interface::msg::Pressure>::SharedPtr ICP10101_publisher_;
    rclcpp::Clock::SharedPtr clock = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);

    
    /**
     * @brief Publish message to ROS2 topic
     * 
     */
    void pres_data_publisher(){
        auto pres_msg = tdk_robokit_interface::msg::Pressure();
        auto header = std_msgs::msg::Header();

        header.stamp = clock->now();
        header.frame_id = "tdk_robokit_icp10101";
        pres_msg.header = header;

        pres_msg.pressure_mb = pressure_mb;
        pres_msg.celsius = celsius;
        pres_msg.height_m = height_m;

        // Publish msg
        ICP10101_publisher_->publish(pres_msg);
    }


};

// Global shared_ptr used for accessing publisher node
std::shared_ptr<ICP10101_Publisher> common_node(nullptr);


/**
 * @brief A friend function to ICP10101_Publisher that helps publishing PRES messages.
  * 
 * @return: void 
 */
static void publish_message(){
    common_node->pres_data_publisher();
}

/**
 * @brief Main driver function that initiates the Publisher and RCL lib
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto ICP10101_publisher_node = std::make_shared<ICP10101_Publisher>();
    common_node = ICP10101_publisher_node;
    rclcpp::spin(ICP10101_publisher_node);
    rclcpp::shutdown();
    return 0;
}