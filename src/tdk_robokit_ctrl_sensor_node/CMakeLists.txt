cmake_minimum_required(VERSION 3.5)
project(tdk_robokit_ctrl_sensor_node)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tdk_robokit_driver REQUIRED)
find_package(tdk_robokit_interface REQUIRED)

# Include directories
include_directories(include/tdk_robokit_ctrl_sensor_node)

add_executable(icm42622_publisher src/icm42622_publisher.cpp src/ros_handlers_weak_hooks.cpp)
ament_target_dependencies(icm42622_publisher rclcpp sensor_msgs tdk_robokit_driver)

add_executable(ads7052_publisher src/ads7052_publisher.cpp src/ros_handlers_weak_hooks.cpp)
ament_target_dependencies(ads7052_publisher rclcpp sensor_msgs tdk_robokit_driver)

add_executable(ak09918_publisher src/ak09918_publisher.cpp src/ros_handlers_weak_hooks.cpp)
ament_target_dependencies(ak09918_publisher rclcpp sensor_msgs tdk_robokit_driver)

add_executable(ch101_publisher src/ch101_publisher.cpp src/ros_handlers_weak_hooks.cpp )
ament_target_dependencies(ch101_publisher rclcpp sensor_msgs tdk_robokit_driver tdk_robokit_interface)

add_executable(icp10101_publisher src/icp10101_publisher.cpp src/ros_handlers_weak_hooks.cpp)
ament_target_dependencies(icp10101_publisher rclcpp sensor_msgs tdk_robokit_driver tdk_robokit_interface)

add_executable(ics43434_publisher src/ics43434_publisher.cpp src/ros_handlers_weak_hooks.cpp)
ament_target_dependencies(ics43434_publisher tdk_robokit_driver tdk_robokit_interface rclcpp sensor_msgs)

add_executable(tdk_robokit_master_publisher src/tdk_robokit_publisher.cpp src/ros_handlers_weak_hooks.cpp)
ament_target_dependencies(tdk_robokit_master_publisher rclcpp sensor_msgs tdk_robokit_driver tdk_robokit_interface)

install(TARGETS
  icm42622_publisher
  ads7052_publisher
  ak09918_publisher
  icp10101_publisher
  ch101_publisher
  ics43434_publisher
  tdk_robokit_master_publisher
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
