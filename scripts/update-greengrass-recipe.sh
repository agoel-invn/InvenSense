#!/bin/bash

stack_name=$1
file_path="greengrass-receipe/recipe.yaml"

# Read values from ROS2Topics and IoTTopics using yq
ROS2Topics=$(yq eval '.ROS2Topics[]' configurations.yaml)
IoTTopics=$(yq eval '.IoTTopics[]' configurations.yaml)

add_topics_to_greengrass_recipe() {
    local topics="$1"
    # Use yq to add the new values to the resources array if not already present
    for topic in "${topics[@]}"; do
        # Check if the resource value is already present in the array
        if ! yq eval '.ComponentConfiguration.DefaultConfiguration.accessControl."aws.greengrass.ipc.mqttproxy"."com.example.PubSubPublisher:pubsub:1".resources | contains(["'"$topic"'"])' "$file_path"; then
            # Add the resource value to the array
            yq eval '.ComponentConfiguration.DefaultConfiguration.accessControl."aws.greengrass.ipc.mqttproxy"."com.example.PubSubPublisher:pubsub:1".resources += ["'"$topic"'"]' -i "$file_path"
            echo "Added $topic to resources"
        else
            echo "$topic is already present in resources"
        fi
    done
}

update_bucket_in_greengrass_recipe() {
    local s3bucket=$(yq eval '.CloudFormationS3Bucket' configurations.yaml)
    s3_uri="s3://$s3bucket/com.invensense.ros2/1.0.0/artifacts/docker-compose.yaml"
    yq eval '.Manifests[0].Artifacts[1].URI = "'"$new_uri"'"' -i $file_path
}

update_ecr_uri_in_greengrass_recipe() {
    local ecr_uri=$(yq eval '.ECRURI' configurations.yaml)
    artifact="docker:$ecr_uri"
    yq eval '.Manifests[0].Artifacts[0].URI = "'"$artifact"'"' -i $file_path

    install_cmd="docker tag $ecr_uri ros-foxy-greengrass-demo:latest"
}