#include<iostream>
#include<chrono>
#include<bits/stdc++.h>

#include "sensor_node.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/clock.hpp"
#include "sensor_msgs/msg/temperature.hpp"
#include "std_msgs/msg/header.hpp"

using namespace std::chrono;
using std::hex;
using std::dec;

static void publish_message();

extern "C" {
int handle_temp_sensor(int);
int serial_data_parser(void);
}

float temperature = 0.0;


/***
 * Helper function to convert 32 bit value in 
 * IEEE format floating point value
 * 
 */

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
 * @brief Callback handler to update GRV data.
 *      
 *        Also publishes the IMU & GRV data to ROS topic.
 * 
 * @param data 
 */

void temp_data_cmd_handler(uint8_t *data){

    data = data + 8; // Skip timetag_us

    uint32_t temp = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    temperature = getFloat(temp);

    // std::cout <<  "temperature: " << getf.f << std::endl;

    /**
     * Publish IMU message on receiving the GRV data.
     * RBK firmware send IMU data followed by GRV data, so the 
     * Publisher publishes  IMU & GRV data together every 10ms
     */
    publish_message();
}

/**
 * @brief ICM42622 ROS2 Publisher for publishing IMU & GRV data 
 * 
 */
class ADS7052_Publisher : public rclcpp::Node
{
public:
    ADS7052_Publisher() : Node("tdk_robokit_ads7052")
    {
        // Create a Publisher
        ADS7052_publisher_ = this->create_publisher<sensor_msgs::msg::Temperature>("tdk_robokit_ads7052", 10);
        RCLCPP_INFO(this->get_logger(), "Initiating Temperature Publisher");

        // Access tdk_robokit_driver to open serial comm to RBK
        serial_openned = serial_data_parser();

        if(!serial_openned)
        {
            RCLCPP_INFO(this->get_logger(), "Serial openned successfully");

            RCLCPP_INFO(this->get_logger(), "Enabling Temp Sensor in RBK");
            enable_sensor = handle_temp_sensor(1);
            RCLCPP_INFO(this->get_logger(), "enable_sensor : %d\n", enable_sensor);
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Serial opening failed... ");
        }
    }

    friend void publish_message();

private:
    int serial_openned;
    int enable_sensor;

    // timer declaration
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Temperature>::SharedPtr ADS7052_publisher_;
    rclcpp::Clock::SharedPtr clock = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);

    /**
     * @brief Publish message to ROS2 topic
     * 
     */
    void temp_data_publisher(){
        auto temp_msg = sensor_msgs::msg::Temperature();
        auto header = std_msgs::msg::Header();

        header.stamp = clock->now();
        header.frame_id = "tdk_robokit_ads7052";
        temp_msg.header = header;

        temp_msg.temperature = temperature;

        // Publish msg
        ADS7052_publisher_->publish(temp_msg);
    }
};

// Global shared_ptr used for accessing publisher node
std::shared_ptr<ADS7052_Publisher> common_node(nullptr);


/**
 * @brief A friend function to ICM42622_Publisher that helps publishing IMU & GRV messages.
  * 
 * @return: void 
 */
static void publish_message(){
    common_node->temp_data_publisher();
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
    auto ADS7052_publisher_node = std::make_shared<ADS7052_Publisher>();
    common_node = ADS7052_publisher_node;
    rclcpp::spin(ADS7052_publisher_node);
    rclcpp::shutdown();
    return 0;
}