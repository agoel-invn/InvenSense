#include<iostream>
#include<chrono>

#include "sensor_node.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/clock.hpp"
#include "sensor_msgs/msg/magnetic_field.hpp"
#include "std_msgs/msg/header.hpp"

using namespace std::chrono;
using std::hex;
using std::dec;

static void publish_message();

extern "C" {
// #include "serial_interface.hpp"
int handle_mag_sensor(int enable);
int serial_data_parser(void);
}

// Globals
float mag_x = 0.0;
float mag_y = 0.0;
float mag_z = 0.0;

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
 * @brief Callback handler to update MAG data.
 *      
 *        Also publishes the MAG data to ROS topic.
 * 
 * @param data 
 */

void mag_data_cmd_handler(uint8_t *data){

    data = data + 8; // Skip timetag_us
    
    uint32_t mag = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    mag_x = getFloat(mag);
    data = data + 4;

    mag = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    mag_y = getFloat(mag);
    data = data + 4;

    mag = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    mag_z = getFloat(mag);

    // std::cout <<  "mag_x: " << dec << mag_x << std::endl;
    // std::cout <<  "mag_y: " << dec << mag_y << std::endl;
    // std::cout <<  "mag_z: " << dec << mag_z << std::endl;
    
    /**
     * Publish message on receiving the MAG data.
     */
    publish_message();
}

/**
 * @brief AK09918 ROS2 Publisher for publishing MAG data 
 * 
 */
class AK09918_Publisher : public rclcpp::Node
{
public:
    AK09918_Publisher() : Node("tdk_robokit_ak09918")
    {
        // Create a Publisher
        AK09918_publisher_ = this->create_publisher<sensor_msgs::msg::MagneticField>("tdk_robokit_ak09918", 10);
        RCLCPP_INFO(this->get_logger(), "Initiating MAG Publisher");

        // Access tdk_robokit_driver to open serial comm to RBK
        serial_openned = serial_data_parser();

        if(!serial_openned)
        {
            RCLCPP_INFO(this->get_logger(), "Serial opened successfully");
            RCLCPP_INFO(this->get_logger(), "Enable Mag in RBK");
            int enable = handle_mag_sensor(1);
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
    rclcpp::Publisher<sensor_msgs::msg::MagneticField>::SharedPtr AK09918_publisher_;
    rclcpp::Clock::SharedPtr clock = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);

    
    /**
     * @brief Publish message to ROS2 topic
     * 
     */
    void mag_data_publisher(){
        auto mag_msg = sensor_msgs::msg::MagneticField();
        auto header = std_msgs::msg::Header();

        header.stamp = clock->now();
        header.frame_id = "tdk_robokit_ak09918";
        mag_msg.header = header;

        mag_msg.magnetic_field.x = mag_x;
        mag_msg.magnetic_field.y = mag_y;
        mag_msg.magnetic_field.z = mag_z;

        // Publish msg
        AK09918_publisher_->publish(mag_msg);
    }


};

// Global shared_ptr used for accessing publisher node
std::shared_ptr<AK09918_Publisher> common_node(nullptr);


/**
 * @brief A friend function to AK09918_Publisher that helps publishing MAG messages.
  * 
 * @return: void 
 */
static void publish_message(){
    common_node->mag_data_publisher();
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
    auto AK09918_publisher_node = std::make_shared<AK09918_Publisher>();
    common_node = AK09918_publisher_node;
    rclcpp::spin(AK09918_publisher_node);
    rclcpp::shutdown();
    return 0;
}