import json
import math
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu, Temperature, MagneticField
from std_msgs.msg import String
from tdk_robokit_interface.msg import RangeData, Pressure, AudioData

class TDKRoboKitCloud(Node):

    def __init__(self):
        super().__init__('tdk_robokit_cloud')

        self.ICM42622_publisher_ = self.create_publisher(
            String,
            'tdk_robokit_icm42622_py',
            10)

        self.ICM42622_subscriber_ = self.create_subscription(
            Imu,
            'tdk_robokit_icm42622',
            self.icm42622_callback,
            10)

        self.CH101_publisher_ = self.create_publisher(
            String,
            'tdk_robokit_ch101_py',
            10)

        self.CH101_subscriber_ = self.create_subscription(
            RangeData,
            'tdk_robokit_ch101',
            self.ch101_callback,
            10)
        
        self.AK09918_publisher_ = self.create_publisher(
            String,
            'tdk_robokit_ak09918_py',
            10)

        self.AK09918_subscriber_ = self.create_subscription(
            MagneticField,
            'tdk_robokit_ak09918',
            self.ak09918_callback,
            10)

        self.ICS43434_publisher_ = self.create_publisher(
            String,
            'tdk_robokit_ics43434_py',
            10)

        self.ICS43434_subscriber_ = self.create_subscription(
            AudioData,
            'tdk_robokit_ics43434',
            self.ics43434_callback,
            10)

        self.ICP10101_publisher_ = self.create_publisher(
            String,
            'tdk_robokit_icp10101_py',
            10)

        self.ICP10101_subscriber_ = self.create_subscription(
            Pressure,
            'tdk_robokit_icp10101',
            self.icp10101_callback,
            10)

        self.ADS7052_publisher_ = self.create_publisher(
            String,
            'tdk_robokit_ads7052_py',
            10)

        self.ADS7052_subscriber_ = self.create_subscription(
            Temperature,
            'tdk_robokit_ads7052',
            self.ads7052_callback,
            10)

    def quaternion_to_euler(self, w, x, y, z):

        # Convert quaternion to Euler angles (roll, pitch, yaw)
        
        # Roll (x-axis rotation)
        sinr_cosp = 2 * (w * x + y * z)
        cosr_cosp = 1 - 2 * (x**2 + y**2)
        roll = math.atan2(sinr_cosp, cosr_cosp)

        # Pitch (y-axis rotation)
        sinp = 2 * (w * y - z * x)
        if abs(sinp) >= 1:
            pitch = math.copysign(math.pi / 2, sinp)  # Use 90 degrees if out of range
        else:
            pitch = math.asin(sinp)

        # Yaw (z-axis rotation)
        siny_cosp = 2 * (w * z + x * y)
        cosy_cosp = 1 - 2 * (y**2 + z**2)
        yaw = math.atan2(siny_cosp, cosy_cosp)

        # Convert radians to degrees
        roll = math.degrees(roll)
        pitch = math.degrees(pitch)
        yaw = math.degrees(yaw)

        return roll, pitch, yaw

    def icm42622_callback(self, imu_msg):

        roll, pitch, yaw = self.quaternion_to_euler( imu_msg.orientation.w, imu_msg.orientation.x, imu_msg.orientation.y, imu_msg.orientation.z)

        # Convert the Imu message to a dictionary
        imu_dict = {
            "header": {
                "stamp": {
                    "sec": imu_msg.header.stamp.sec,
                    "nanosec": imu_msg.header.stamp.nanosec,
                },
                "frame_id": imu_msg.header.frame_id
            },
            "orientation": {
                "x": imu_msg.orientation.x,
                "y": imu_msg.orientation.y,
                "z": imu_msg.orientation.z,
                "w": imu_msg.orientation.w,
                "roll": roll,
                "pitch": pitch,
                "yaw": yaw
            },
            "linear_acceleration": {
                "x": imu_msg.linear_acceleration.x,
                "y": imu_msg.linear_acceleration.y,
                "z": imu_msg.linear_acceleration.z
            },
            "angular_velocity": {
                "x": imu_msg.angular_velocity.x,
                "y": imu_msg.angular_velocity.y,
                "z": imu_msg.angular_velocity.z
            }
        }

        message = String()
        message.data = json.dumps(imu_dict)
        self.get_logger().info(f"Publishing: \"{message.data}\" on tdk_robokit_icm42622_py")
        self.ICM42622_publisher_.publish(message)

    def ch101_callback(self, range_msg):
        # Convert the chirp message to a dictionary
        range_dict = {
            "header": {
                "stamp": {
                    "sec": range_msg.header.stamp.sec,
                    "nanosec": range_msg.header.stamp.nanosec,
                },
                "frame_id": range_msg.header.frame_id
            },
            "ULTRASOUND": range_msg.ULTRASOUND,
            "INFRARED": range_msg.INFRARED,
            "radiation_type": range_msg.radiation_type,
            "field_of_view": range_msg.field_of_view,
            "min_range": range_msg.min_range,
            "max_range": range_msg.max_range,
            "range": range_msg.range,
            "sensor_id": range_msg.sensor_id
        }

        message = String()
        message.data = json.dumps(range_dict)
        self.get_logger().info(f"Publishing: \"{message.data}\" on tdk_robokit_ch101_py")
        self.CH101_publisher_.publish(message)

    def ak09918_callback(self, mag_msg):
        # Convert the Mag message to a dictionary
        mag_dict = {
            "header": {
                "stamp": {
                    "sec": mag_msg.header.stamp.sec,
                    "nanosec": mag_msg.header.stamp.nanosec,
                },
                "frame_id": mag_msg.header.frame_id
            },
            "magnetic_field": {
                "x": mag_msg.magnetic_field.x,
                "y": mag_msg.magnetic_field.y,
                "z": mag_msg.magnetic_field.z
            },
            "magnetic_field_covariance": mag_msg.magnetic_field_covariance.tolist()
        }

        message = String()
        message.data = json.dumps(mag_dict)
        self.get_logger().info(f"Publishing: \"{message.data}\" on tdk_robokit_ak09918_py")
        self.AK09918_publisher_.publish(message)
    
    def ics43434_callback(self, audio_msg):
        # Convert the Audio message to a dictionary
        audio_dict = {
            "header": {
                "stamp": {
                    "sec": audio_msg.header.stamp.sec,
                    "nanosec": audio_msg.header.stamp.nanosec,
                },
                "frame_id": audio_msg.header.frame_id
            },
            "data": audio_msg.data.tolist()
        }

        message = String()
        message.data = json.dumps(audio_dict)
        self.get_logger().info(f"Publishing: \"{message.data}\" on tdk_robokit_ics43434_py")
        self.ICS43434_publisher_.publish(message)

    def icp10101_callback(self, pressure_msg):
        # Convert the pressure message to a dictionary
        pressure_dict = {
            "header": {
                "stamp": {
                    "sec": pressure_msg.header.stamp.sec,
                    "nanosec": pressure_msg.header.stamp.nanosec,
                },
                "frame_id": pressure_msg.header.frame_id
            },
            "pressure_mb": pressure_msg.pressure_mb,
            "celsius": pressure_msg.celsius,
            "height_m": pressure_msg.height_m
        }

        message = String()
        message.data = json.dumps(pressure_dict)
        self.get_logger().info(f"Publishing: \"{message.data}\" on tdk_robokit_icp10101_py")
        self.ICP10101_publisher_.publish(message)

    def ads7052_callback(self, temp_msg):
        # Convert the Imu message to a dictionary
        temp_dict = {
            "header": {
                "stamp": {
                    "sec": temp_msg.header.stamp.sec,
                    "nanosec": temp_msg.header.stamp.nanosec,
                },
                "frame_id": temp_msg.header.frame_id
            },
            "temperature": temp_msg.temperature,
            "variance": temp_msg.variance
        }

        message = String()
        message.data = json.dumps(temp_dict)
        self.get_logger().info(f"Publishing: \"{message.data}\" on tdk_robokit_ads7052_py")
        self.ADS7052_publisher_.publish(message)

def main(args=None):
    rclpy.init(args=args)
    tdk_robokit_publisher = TDKRoboKitCloud()
    rclpy.spin(tdk_robokit_publisher)
    tdk_robokit_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()