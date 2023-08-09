#!/bin/bash

source "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")/utils.sh"

ROS2_VERSION_NUMBER=$(python3 -c "import version; print(version.__version__);")
nechon "Packaging ROS2 drivers version ${ROS2_VERSION_NUMBER}"
try zip -r ROS_Cpp_drivers_v${ROS2_VERSION_NUMBER}.zip tdk_robokit_driver/ tdk_robokit_interface/ tdk_robokit_ctrl_sensor_node/
