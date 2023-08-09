#!/usr/bin/env bash

source "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")/utils.sh"

# check_root
# (( ${#} <= 1 )) && die "Usage: $0 <sonar_account_uid> <sonar_account_name>"
ros2_root_dir=${1:-~/ros2_foxy}

nechon "Downloading ROS2 source code"
try mkdir -p ${ros2_root_dir}/src
try pushd ${ros2_root_dir}
try wget https://raw.githubusercontent.com/ros2/ros2/foxy/ros2.repos
try vcs import src < ros2.repos

nechon "Initializing ROS2 workspace"
try sudo rosdep init
try rosdep update
try rosdep install --from-paths src --ignore-src -y --skip-keys "fastcdr rti-connext-dds-5.3.1 urdfdom_headers"

nechon "Building ROS2 workspace"
try colcon build --symlink-install --executor sequential

necho "ROS2 workspace ${ros2_root_dir} is ready to be used"
echo "Please source ${ros2_root_dir}/install/setup.sh"
