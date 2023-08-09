cmake_minimum_required(VERSION 3.5)
project(tdk_robokit_driver)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

add_compile_options(-Wall -Wextra -Wpedantic -Wunused-parameter)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic -Wunused-parameter)
# endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tdk_robokit_interface REQUIRED)
find_package(Threads REQUIRED) # pthread
find_library(LIBRT rt) # mqueue

# Include directories
include_directories(include/tdk_robokit_driver)
include_directories(../tdk_robokit_ctrl_sensor_node/include/tdk_robokit_ctrl_sensor_node)

# add_executable(serial_interface src/serial_interface.c src/msg_handlers.c)
add_library(${PROJECT_NAME} SHARED src/serial_interface.c src/msg_handlers.c)
target_link_libraries(${PROJECT_NAME} Threads::Threads ${LIBRT})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  include
)

ament_target_dependencies(
  ${PROJECT_NAME}
  Threads
  rclcpp
)

# INSTALL
install(
  TARGETS ${PROJECT_NAME}
  DESTINATION lib
)
install(
  DIRECTORY include/
  DESTINATION include
)

## EXPORTS
ament_export_include_directories(
  include
)
ament_export_libraries(
  ${PROJECT_NAME}
)
ament_export_dependencies(
  Threads
  rclcpp
)

ament_package()
