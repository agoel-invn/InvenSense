cmake_minimum_required(VERSION 3.5)
project(tdk_robokit_interface)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)


rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/InvnQuaternion.msg"
  "msg/ObstacleDetectionOut.msg"
  "msg/ChAlgo.msg"
  "msg/Ch.msg"
  "msg/Debug.msg"
  "msg/Imu.msg"
  "msg/PdOut.msg"
  "msg/Status.msg"
  "msg/Pressure.msg"
  "msg/AudioData.msg"
  "msg/RangeData.msg"
  DEPENDENCIES std_msgs geometry_msgs builtin_interfaces sensor_msgs visualization_msgs
 )

 ament_export_dependencies(rosidl_default_runtime)

ament_package()
