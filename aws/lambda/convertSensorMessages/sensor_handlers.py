import boto3
import json
import math
import os

class SensorEventHander:

    def __init__(self):
        self.iot_client = boto3.client(os.environ["IOT_CLIENT"])

    def handle_event(self, sensor_type, message_payload, topic_to_publish=None):
        if sensor_type == os.environ["IMU_FRAME"]:
            return IMUHandler().handle_event(message_payload, os.environ["IMU_TOPIC_TO_PUBLISH"])
        elif sensor_type == os.environ["TEMPERATURE_FRAME"]:
            TemperatureHandler().handle_event(message_payload, os.environ["PRESSURE_TOPIC_TO_PUBLISH"])
        elif sensor_type == os.environ["PRESSURE_FRAME"]:
            PressureHandler().handle_event(message_payload, os.environ["PRESSURE_TOPIC_TO_PUBLISH"])
        elif sensor_type == os.environ["CHIRP_FRAME"]:
            ChirpHandler().handle_event(message_payload, os.environ["CHIRP_TOPIC_TO_PUBLISH"])
        elif sensor_type == os.environ["MICROPHONE_FRAME"]:
            MicrophoneHandler().handle_event(message_payload, os.environ["MICROPHONE_TOPIC_TO_PUBLISH"])
        elif sensor_type == os.environ["MAGNETOMETER_FRAME"]:
            MagnetometerHandler().handle_event(message_payload, os.environ["MAGNETOMETER_TOPIC_TO_PUBLISH"])
        elif sensor_type == os.environ["CAMERA_FRAME"]:
            CameraHandler().handle_event(message_payload, os.environ["CAMERA_TOPIC_TO_PUBLISH"])
        elif sensor_type == os.environ["LIDAR_FRAME"]:
            LidarHandler().handle_event(message_payload, os.environ["LIDAR_TOPIC_TO_PUBLISH"])
        else:
            print("Unknown Sensor Type")
            # TODO: Add more handlers here

class IMUHandler(SensorEventHander):

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

    def handle_event(self, message_payload, topic_to_publish):
        roll, pitch, yaw = self.quaternion_to_euler(message_payload["orientation"]["w"], message_payload["orientation"]["x"], message_payload["orientation"]["y"], message_payload["orientation"]["z"])
    
        message_payload["orientation"]["roll"] = roll
        message_payload["orientation"]["pitch"] = pitch
        message_payload["orientation"]["yaw"] = yaw

        print(f"Publishing {message_payload} on topic: {topic_to_publish}")

        try:
            response = self.iot_client.publish(
                topic=topic_to_publish,
                qos=1,
                payload=json.dumps(message_payload)
            )
            print("IMU message published successfully.")

        except Exception as e:
            print("Error publishing IMU message: ", e)

        return message_payload
    
class TemperatureHandler(SensorEventHander):
   
    def handle_event(self, message_payload, topic_to_publish):
        
        print(f"Publishing {message_payload} on topic: {topic_to_publish}")

        try:
            response = self.iot_client.publish(
                topic=topic_to_publish,
                qos=1,
                payload=json.dumps(message_payload)
            )
            print("Temperature message published successfully.")
            
        except Exception as e:
            print("Error publishing Temperature message: ", e)
            
        return message_payload

class PressureHandler(SensorEventHander):
    
    def handle_event(self, message_payload, topic_to_publish):
        print(f"Publishing {message_payload} on topic: {topic_to_publish}")
        try:
            response = self.iot_client.publish(
                topic=topic_to_publish,
                qos=1,
                payload=json.dumps(message_payload)
            )
            print("Pressure message published successfully.")
        except Exception as e:
            print("Error publishing Pressure message: ", e)
            
        return message_payload

class ChirpHandler(SensorEventHander):

    def handle_event(self, message_payload, topic_to_publish):
        print(f"Publishing {message_payload} on topic: {topic_to_publish}")
        try:
            response = self.iot_client.publish(
                topic=topic_to_publish,
                qos=1,
                payload=json.dumps(message_payload)
            )
            print("Chirp message published successfully.")
        except Exception as e:
            print("Error publishing Chirp message: ", e)
            
        return message_payload
    
class MicrophoneHandler(SensorEventHander):

    def handle_event(self, message_payload, topic_to_publish):
        print(f"Publishing {message_payload} on topic: {topic_to_publish}")
        try:
            response = self.iot_client.publish(
                topic=topic_to_publish,
                qos=1,
                payload=json.dumps(message_payload)
            )
            print("Microphone message published successfully.")
        except Exception as e:
            print("Error publishing Microphone message: ", e)
            
        return message_payload
    
class MagnetometerHandler(SensorEventHander):
  
    def handle_event(self, message_payload, topic_to_publish):
        print(f"Publishing {message_payload} on topic: {topic_to_publish}")
        try:
            response = self.iot_client.publish(
                topic=topic_to_publish,
                qos=1,
                payload=json.dumps(message_payload)
            )
            print("Magnetometer message published successfully.")
        except Exception as e:
            print("Error publishing Magnetometer message: ", e)
            
        return message_payload
    
class CameraHandler(SensorEventHander):

    def handle_event(self, message_payload, topic_to_publish):
        print(f"Publishing {message_payload} on topic: {topic_to_publish}")
        try:
            response = self.iot_client.publish(
                topic=topic_to_publish,
                qos=1,
                payload=json.dumps(message_payload)
            )
            print("Camera message published successfully.")
        except Exception as e:
            print("Error publishing Camera message: ", e)
            
        return message_payload
    
class LidarHandler(SensorEventHander):

    def handle_event(self, message_payload, topic_to_publish):
        print(f"Publishing {message_payload} on topic: {topic_to_publish}")
        try:
            response = self.iot_client.publish(
                topic=topic_to_publish,
                qos=1,
                payload=json.dumps(message_payload)
            )
            print("Lidar message published successfully.")
        except Exception as e:
            print("Error publishing Lidar message: ", e)
            
        return message_payload