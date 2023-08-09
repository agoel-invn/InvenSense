#!/bin/bash

source "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")/utils.sh"

(( ${#} != 1 )) && die "Usage: ${0} <ros2 workspace root>"

ROS2_FOXY_WS=${1}

try source ${ROS2_FOXY_WS}/install/setup.sh
rosdep install -i --from-path * --rosdistro foxy -y || warn "This is failing but let's continue for now"
try colcon build
