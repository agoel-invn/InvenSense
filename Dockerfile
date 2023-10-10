ARG ROS_DISTRO=humble

FROM ros:${ROS_DISTRO}-ros-base AS build-base
SHELL ["/bin/bash", "-c"]

RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys F42ED6FBAB17C654
RUN apt-get update && apt-get install python3-pip -y
RUN apt-get update && apt-get install ros-$ROS_DISTRO-example-interfaces
RUN python3 -m pip install awsiotsdk
RUN pip install setuptools==58.2.0

RUN mkdir -p /ws/src
WORKDIR /ws
COPY src /ws/src

RUN . /opt/ros/$ROS_DISTRO/setup.sh && \
    colcon build --build-base src/build --install-base /opt/ros_demos

# RUN colcon build --packages-select tdk_robokit_interface
# RUN colcon build --packages-select tdk_robokit_driver
# RUN colcon build --packages-select tdk_robokit_ctrl_robot_node
# RUN colcon build --packages-select tdk_robokit_cloud
# RUN colcon build --packages-select tdk_robokit_ctrl_sensor_node

WORKDIR /
COPY app_entrypoint.sh /app_entrypoint.sh
RUN chmod +x /app_entrypoint.sh
ENTRYPOINT ["/app_entrypoint.sh"]