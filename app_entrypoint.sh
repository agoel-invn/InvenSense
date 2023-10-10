#!/bin/bash
set -e

# setup ros2 environment
source "/opt/ros/humble/setup.bash"
source "/opt/ros_demos/setup.bash"
exec "$@"