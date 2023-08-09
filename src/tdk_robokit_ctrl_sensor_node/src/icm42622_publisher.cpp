#include<iostream>
#include<chrono>

#include "sensor_node.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/clock.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "std_msgs/msg/header.hpp"

using namespace std::chrono;
using namespace std;
using std::hex;
using std::dec;

static void publish_message();

extern "C" {
int serial_data_parser(void);
int handle_imu_sensor(int enable);
}

// Globals
float ACCEL_G_TO_MPS2 = 9.80665;
float GYRO_DPS_TO_RPS = 3.14159 / 180;
/*
    Accel data is calibrated in multiples of g in Q16
    format in RoboKit firmware. Update value of FSR if
    a diff value is chosen.
*/
float ICM42688_ACCEL_FSR_G = 16.0;
/*
    Gyro data is calibrated gyro in dps to Q31 with
    sensitivity of 2000 dps in RoboKit firmware.
    Update value of FSR if a diff value is chosen.
*/
float ICM42688_GYRO_FSR_DPS = 2000.0;
float ACCEL_RES_MPSS = (ACCEL_G_TO_MPS2) * (ICM42688_ACCEL_FSR_G / 32768.0);
float GYRO_RES_RPS = (GYRO_DPS_TO_RPS) * (ICM42688_GYRO_FSR_DPS / 32768.0);

float linear_acceleration_x = 0.0;
float linear_acceleration_y = 0.0;
float linear_acceleration_z = 0.0;
float angular_velocity_x = 0.0;
float angular_velocity_y = 0.0;
float angular_velocity_z = 0.0;
float orientation_x = 0.0;
float orientation_y = 0.0;
float orientation_z = 0.0;
float orientation_w = 0.0;

const int two_pow_30 = 1<<30;

/**
 * @brief Callback handler to update IMU data
 * 
 * @param data 
 */
void imu_data_cmd_handler(uint8_t *data){

        data = data + 8; // Skip timetag_us
        
        uint16_t acceleration_x = (uint16_t) *data++;
        acceleration_x =  ((uint16_t) acceleration_x | (((uint16_t)(*data++)) << 8)) ;
        linear_acceleration_x =  1.0f * (int16_t) acceleration_x * ACCEL_RES_MPSS;

        uint16_t acceleration_y = (uint16_t) *data++;
        acceleration_y =  ((uint16_t) acceleration_y | (((uint16_t)(*data++)) << 8)) ;
        linear_acceleration_y =  1.0f * (int16_t) acceleration_y * ACCEL_RES_MPSS;

        uint16_t acceleration_z = (uint16_t) *data++;
        acceleration_z =  ((uint16_t) acceleration_z | (((uint16_t)(*data++)) << 8)) ;
        linear_acceleration_z =  1.0f * (int16_t) acceleration_z * ACCEL_RES_MPSS;

        uint16_t velocity_x = (uint16_t) *data++;
        velocity_x =  ((uint16_t) velocity_x | (((uint16_t)(*data++)) << 8)) ;
        angular_velocity_x =  1.0f * (int16_t) velocity_x * GYRO_RES_RPS;

        uint16_t velocity_y = (uint16_t) *data++;
        velocity_y =  ((uint16_t) velocity_y | (((uint16_t)(*data++)) << 8)) ;
        angular_velocity_y =  1.0f * (int16_t) velocity_y * GYRO_RES_RPS;

        uint16_t velocity_z = (uint16_t) *data++;
        velocity_z =  ((uint16_t) velocity_z | (((uint16_t)(*data++)) << 8)) ;
        angular_velocity_z =  1.0f * (int16_t) velocity_z * GYRO_RES_RPS;
    }

/**
 * @brief Callback handler to update GRV data.
 *      
 *        Also publishes the IMU & GRV data to ROS topic.
 * 
 * @param data 
 */

void grv_data_cmd_handler(uint8_t *data){

    data = data + 8; // Skip timetag_us

    uint32_t quat = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    orientation_w = (1.0f * (int32_t) quat) / ((float) two_pow_30);
    data = data + 4;

    quat = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    orientation_x = (1.0f * (int32_t) quat) / ((float) two_pow_30);
    data = data + 4;

    quat = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    orientation_y = (1.0f * (int32_t) quat) / ((float) two_pow_30);
    data = data + 4;

    quat = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);
    orientation_z = (1.0f * (int32_t) quat) / ((float) two_pow_30);

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
class ICM42622_Publisher : public rclcpp::Node
{
public:
    ICM42622_Publisher() : Node("tdk_robokit_icm42622")
    {
        // Create a Publisher
        ICM42622_publisher_ = this->create_publisher<sensor_msgs::msg::Imu>("tdk_robokit_icm42622", 10);
        RCLCPP_INFO(this->get_logger(), "Initiating IMU Publisher");

        // Access tdk_robokit_driver to open serial comm to RBK
        serial_opened = serial_data_parser();

        if(!serial_opened)
        {
            RCLCPP_INFO(this->get_logger(), "Serial opened successfully");
            RCLCPP_INFO(this->get_logger(), "Enable IMU sensor from RBK");
            handle_imu_sensor(1);
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Serial opening failed... ");
        }
    }

    friend void publish_message();

private:

    int serial_opened;

    // timer declaration
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr ICM42622_publisher_;
    rclcpp::Clock::SharedPtr clock = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);

    
    /**
     * @brief Publish message to ROS2 topic
     * 
     */
    void imu_data_publisher(){
        auto imu_msg = sensor_msgs::msg::Imu();
        auto imu_header = std_msgs::msg::Header();

        imu_header.stamp = clock->now();
        imu_header.frame_id = "tdk_robokit_icm42622";
        imu_msg.header = imu_header;

        imu_msg.linear_acceleration.x = linear_acceleration_x;
        imu_msg.linear_acceleration.y = linear_acceleration_y;
        imu_msg.linear_acceleration.z = linear_acceleration_z;

        imu_msg.angular_velocity.x = angular_velocity_x;
        imu_msg.angular_velocity.y = angular_velocity_y;
        imu_msg.angular_velocity.z = angular_velocity_z;

        imu_msg.orientation.w = orientation_w;
        imu_msg.orientation.x = orientation_x;
        imu_msg.orientation.y = orientation_y;
        imu_msg.orientation.z = orientation_z;

        // Publish imu_msg
        ICM42622_publisher_->publish(imu_msg);
    }
};

// Global shared_ptr used for accessing publisher node
std::shared_ptr<ICM42622_Publisher> common_node(nullptr);

/**
 * @brief A friend function to ICM42622_Publisher that helps publishing IMU & GRV messages.
  * 
 * @return: void 
 */
static void publish_message(){
    common_node->imu_data_publisher();
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
    auto ICM42622_publisher_node = std::make_shared<ICM42622_Publisher>();
    common_node = ICM42622_publisher_node;
    rclcpp::spin(ICM42622_publisher_node);
    rclcpp::shutdown();
    return 0;
}