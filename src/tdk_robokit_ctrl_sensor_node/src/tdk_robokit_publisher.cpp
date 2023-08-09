#include<iostream>
#include<chrono>

#include "sensor_node.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/clock.hpp"
#include "std_msgs/msg/header.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/temperature.hpp"
#include "sensor_msgs/msg/magnetic_field.hpp"
#include "tdk_robokit_interface/msg/range_data.hpp"
#include "tdk_robokit_interface/msg/pressure.hpp"
#include "tdk_robokit_interface/msg/audio_data.hpp"

#define AUDIO_MSG_MAX_SIZE 256

using namespace std::chrono;
using std::hex;
using std::dec;

static void publish_imu_message();
static void publish_temp_message();
static void publish_mag_message();
static void publish_chirp_message();
static void publish_pres_message();
static void publish_audio_message();

extern "C" {
int serial_data_parser(void);
int handle_temp_sensor(int enable);
int handle_imu_sensor(int enable);
int handle_mag_sensor(int enable);
int handle_pres_sensor(int enable);
int handle_asic_sensor(int enable);
int handle_audio_sensor(int enable);
}

typedef enum robokit_sensor_id_enum
{
	CH_ID_IMU,
	CH_ID_MAG,
	CH_ID_TEMP,
	CH_ID_AUDIO,
	CH_ID_CHIRP,
	CH_ID_PRESSURE
} rk_sensor_id_t;

// IMU GRV Globals
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

// Temp Globals
float temperature = 0.0;

// Mag Globals
float mag_x = 0.0;
float mag_y = 0.0;
float mag_z = 0.0;

// Chirp Globals
uint32_t range_cm = 0;
uint8_t rx_sensor_id = 100, tx_sensor_id = 100;

// Pres Globals
float pressure_mb = 0.0;
float celsius = 0.0;
float height_m = 0.0;

// Audio Globals
uint8_t audio_data[AUDIO_MSG_MAX_SIZE] = {0};

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

    range_cm = (uint32_t) (*(data+3) << 24) |  (uint32_t) (*(data+2) << 16) | (uint32_t) (*(data+1) << 8) | (uint32_t) *(data);

    /**
     * Publish CHIRP message on receiving the data.
     */
    if(rx_sensor_id == tx_sensor_id)
        publish_chirp_message();
}

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
    publish_imu_message();

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

    /**
     * Publish IMU message on receiving the GRV data.
     * RBK firmware send IMU data followed by GRV data, so the 
     * Publisher publishes  IMU & GRV data together every 10ms
     */
    publish_temp_message();
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
    
    /**
     * Publish message on receiving the MAG data.
     */
    publish_mag_message();
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
    publish_pres_message();
}

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
    publish_audio_message();
}



/**
 * @brief ICM42622 ROS2 Publisher for publishing IMU & GRV data 
 * 
 */
class tdk_roboKit_Publisher : public rclcpp::Node
{
public:
    tdk_roboKit_Publisher() : Node("tdk_robokit_master_publisher")
    {
        // Access tdk_robokit_driver to open serial comm to RBK
        serial_openned = serial_data_parser();

        if(!serial_openned)
        {
            RCLCPP_INFO(this->get_logger(), "Serial opened successfully");

            handle_temp_sensor(1);
            handle_imu_sensor(1);
            handle_mag_sensor(1);
            handle_pres_sensor(1);
            handle_asic_sensor(1);
            handle_audio_sensor(1);

            // Create All Publisher
            RCLCPP_ERROR(this->get_logger(), "Starting ICM42622_publisher");
            ICM42622_publisher_ = this->create_publisher<sensor_msgs::msg::Imu>("tdk_robokit_icm42622", 10);
            RCLCPP_ERROR(this->get_logger(), "Starting ADS7052_publisher");
            ADS7052_publisher_ = this->create_publisher<sensor_msgs::msg::Temperature>("tdk_robokit_ads7052", 10);
            RCLCPP_ERROR(this->get_logger(), "Starting AK09918_publisher");
            AK09918_publisher_ = this->create_publisher<sensor_msgs::msg::MagneticField>("tdk_robokit_ak09918", 10);
            RCLCPP_ERROR(this->get_logger(), "Starting CH101_publisher");
            CH101_publisher_ = this->create_publisher<tdk_robokit_interface::msg::RangeData>("tdk_robokit_ch101", 10);
            RCLCPP_ERROR(this->get_logger(), "Starting ICP10101_publisher");
            ICP10101_publisher_ = this->create_publisher<tdk_robokit_interface::msg::Pressure>("tdk_robokit_icp10101", 10);
            RCLCPP_ERROR(this->get_logger(), "Starting ICS43434_publisher");
            ICS43434_publisher_ = this->create_publisher<tdk_robokit_interface::msg::AudioData>("tdk_robokit_ics43434", 10);
            RCLCPP_INFO(this->get_logger(), "Started All publishers");
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Serial opening failed... ");
        }

    }

    // friend void publish_imu_message();


    /**
     * @brief Publish IMU & GRV message to ROS2 topic
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

    /**
     * @brief Publish Temp message to ROS2 topic
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

    /**
     * @brief Publish Mag message to ROS2 topic
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

    /**
     * @brief Publish Chirp (range) message to ROS2 topic
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
        ch_msg.range = range_cm / 100;
        ch_msg.sensor_id = rx_sensor_id;

        // Publish imu_msg
        CH101_publisher_->publish(ch_msg);
    }

    /**
     * @brief Publish pressure message to ROS2 topic
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

private:

    int serial_openned;

    // timer declaration
    rclcpp::Clock::SharedPtr clock = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);

    // publishers declaration
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr ICM42622_publisher_;
    rclcpp::Publisher<sensor_msgs::msg::Temperature>::SharedPtr ADS7052_publisher_;
    rclcpp::Publisher<sensor_msgs::msg::MagneticField>::SharedPtr AK09918_publisher_;
    rclcpp::Publisher<tdk_robokit_interface::msg::RangeData>::SharedPtr CH101_publisher_;
    rclcpp::Publisher<tdk_robokit_interface::msg::Pressure>::SharedPtr ICP10101_publisher_;
    rclcpp::Publisher<tdk_robokit_interface::msg::AudioData>::SharedPtr ICS43434_publisher_;
};

// Global shared_ptr used for accessing publisher node
std::shared_ptr<tdk_roboKit_Publisher> common_node(nullptr);

/**
 * @brief A friend function to tdk_roboKit_Publisher that helps publishing IMU & GRV messages.
  * 
 * @return: void 
 */
static void publish_imu_message(){
    common_node->imu_data_publisher();
}

/**
 * @brief A friend function to ICM42622_Publisher that helps publishing IMU & GRV messages.
  * 
 * @return: void 
 */
static void publish_temp_message(){
    common_node->temp_data_publisher();
}

/**
 * @brief A friend function to AK09918_Publisher that helps publishing MAG messages.
  * 
 * @return: void 
 */
static void publish_mag_message(){
    common_node->mag_data_publisher();
}

/**
 * @brief A friend function to CH101_Publisher that helps publishing IMU & GRV messages.
  * 
 * @return: void 
 */
static void publish_chirp_message(){
    common_node->chirp_data_publisher();
}

/**
 * @brief A friend function to ICP10101_Publisher that helps publishing PRES messages.
  * 
 * @return: void 
 */
static void publish_pres_message(){
    common_node->pres_data_publisher();
}

/**
 * @brief A friend function to ics43434_Publisher that helps publishing Audio messages.
  * 
 * @return: void 
 */
static void publish_audio_message(){
    common_node->audio_data_publisher();
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
    auto tdk_robokit_publisher_node = std::make_shared<tdk_roboKit_Publisher>();
    common_node = tdk_robokit_publisher_node;
    rclcpp::spin(tdk_robokit_publisher_node);
    rclcpp::shutdown();
    return 0;
}