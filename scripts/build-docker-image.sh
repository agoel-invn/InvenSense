#!/bin/bash

# 1. Update docker-compose.yaml with ros topics
ros2_topics_list=$(yq e '.iot.ros2_topics | join(",")' ../configurations/configuration.yaml)

iot_topics_list=$(yq e '.iot.iot_topics | join(",")' ../configurations/configuration.yaml)

yq e -i '.services.greengrass_bridge.command = "ros2 launch greengrass_bridge greengrass_bridge.launch.py ros_topics:=['"$ros2_topics_list"'] iot_topics:=['"$iot_topics_list"']"' ../docker/docker-compose.yaml

# cd ../docker/
# sudo DOCKER_BUILDKIT=1 docker-compose build