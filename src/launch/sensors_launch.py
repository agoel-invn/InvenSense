from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='tdk_robokit_ctrl_sensor_node',
            namespace='',
            executable='tdk_robokit_master_publisher',
            name='master'
        ),
        Node(
            package='tdk_robokit_cloud',
            namespace='',
            executable='tdk_robokit_cloud_publisher',
            name='cloud'
        )
    ])