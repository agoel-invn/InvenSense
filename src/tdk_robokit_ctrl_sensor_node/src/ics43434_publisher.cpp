#include<iostream>
#include<chrono>

#include "sensor_node.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/clock.hpp"
#include "std_msgs/msg/header.hpp"
#include "tdk_robokit_interface/msg/audio_data.hpp"

using namespace std::chrono;
using std::dec;

static void publish_message();

extern "C" {
    int handle_audio_sensor(int);
    int serial_data_parser(void);
}

#define AUDIO_MSG_MAX_SIZE 256

// Globals
uint8_t audio_data[AUDIO_MSG_MAX_SIZE] = {0};

/**
 * @brief Callback handler to update Audio data.
 *      
 *        Also publishes the Audio data to ROS topic.
 * 
 * @param data 
 */

void audio_data_cmd_handler(uint8_t *data, uint8_t data_size){

    memset(&audio_data, 0, sizeof(audio_data));
    memcpy(audio_data, data, data_size);
    
    /**
     * Publish message on receiving the Audio data.
     */
    publish_message();
}


/**
 * @brief ICS43434 ROS2 Publisher for publishing Audio data 
 * 
 */
class ICS43434_Publisher : public rclcpp::Node
{
public:
    ICS43434_Publisher() : Node("tdk_robokit_ics43434")
    {
        // Create a Publisher
        ICS43434_publisher_ = this->create_publisher<tdk_robokit_interface::msg::AudioData>("tdk_robokit_ics43434", 10);
        RCLCPP_INFO(this->get_logger(), "Initiating Audio Publisher");

        // Access tdk_robokit_driver to open serial comm to RBK
        serial_opened = serial_data_parser();

        if(!serial_opened)
        {
            RCLCPP_INFO(this->get_logger(), "Serial opened successfully");
            RCLCPP_INFO(this->get_logger(), "Enabling Audio Sensor in RBK");
            handle_audio_sensor(1);
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Serial opening failed... ");
        }

    }

    friend void publish_message();

private:

    int serial_opened;

    rclcpp::Publisher<tdk_robokit_interface::msg::AudioData>::SharedPtr ICS43434_publisher_;
    rclcpp::Clock::SharedPtr clock = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);

    
    /**
     * @brief Publish message to ROS2 topic
     * 
     */
    void audio_data_publisher(){

        auto audio_msg = tdk_robokit_interface::msg::AudioData();
        auto header = std_msgs::msg::Header();

        header.stamp = clock->now();
        header.frame_id = "tdk_robokit_ics43434";
        audio_msg.header = header;

        memcpy(&audio_msg.data, audio_data, sizeof(audio_data));

        // Publish msg
        ICS43434_publisher_->publish(audio_msg);
    }
};

// Global shared_ptr used for accessing publisher node
std::shared_ptr<ICS43434_Publisher> common_node(nullptr);


/**
 * @brief A friend function to ics43434_Publisher that helps publishing Audio messages.
  * 
 * @return: void 
 */
static void publish_message(){
    common_node->audio_data_publisher();
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
    auto ICS43434_publisher_node = std::make_shared<ICS43434_Publisher>();
    common_node = ICS43434_publisher_node;
    rclcpp::spin(ICS43434_publisher_node);
    rclcpp::shutdown();
    return 0;
}