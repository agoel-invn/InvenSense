#!/bin/bash

stack_name=$(yq eval '.cloudformation.stack_name' ../configurations/configuration.yaml)
file_path="../aws/greengrass/recipe.yaml"

# Read values from ROS2Topics and IoTTopics using yq
ros2_topics=$(yq eval '.iot.ros2_topics[]' ../configurations/configuration.yaml)
iot_topics=$(yq eval '.iot.iot_topics[]' ../configurations/configuration.yaml)

# Function to add topics to recipe.yaml
add_topics_to_recipe() {
    local topics=$1
    for topic in $topics; do
        # Check if the topic already exists in recipe.yaml
        exists=$(yq eval ".ComponentConfiguration.DefaultConfiguration.accessControl.\"aws.greengrass.ipc.mqttproxy\".\"com.example.PubSubPublisher:pubsub:1\".resources[] | select(. == \"$topic\")" $file_path)
    
        # If the topic doesn't exist, add it to recipe.yaml
        if [[ -z "$exists" ]]; then
            yq eval ".ComponentConfiguration.DefaultConfiguration.accessControl.\"aws.greengrass.ipc.mqttproxy\".\"com.example.PubSubPublisher:pubsub:1\".resources += [\"$topic\"]" -i $file_path
        fi
    done
}

update_bucket_in_greengrass_recipe() {
    local s3bucket=$(yq eval '.cloudformation.s3bucket' ../configurations/configuration.yaml)
    s3_uri="s3://$s3bucket/com.invensense.cloud/1.0.0/artifacts/docker-compose.yaml"
    yq eval '.Manifests[0].Artifacts[1].URI = "'"$s3_uri"'"' -i $file_path
}

update_ecr_uri_in_greengrass_recipe() {
    local ecr_uri=$(yq eval '.ecr.repository_uri' ../configurations/configuration.yaml)
    artifact="docker:$ecr_uri:latest"
    yq eval '.Manifests[0].Artifacts[0].URI = "'"$artifact"'"' -i $file_path

    install_cmd="docker tag $ecr_uri:latest invensense-ros2-cloud:latest"
    yq eval '.Manifests[0].Lifecycle.Install = "'"$install_cmd"'"' -i $file_path
}

upload_recipy_to_aws_bucket() {

    local s3bucket=$(yq eval '.cloudformation.s3bucket' ../configurations/configuration.yaml)
    s3_uri="s3://$s3bucket/com.invensense.cloud/1.0.0/artifacts/docker-compose.yaml"

    aws s3 cp ../docker/docker-compose.yaml $s3_uri
}


# Add the topics
add_topics_to_recipe "$ros2_topics"
add_topics_to_recipe "$iot_topics"
update_bucket_in_greengrass_recipe
update_ecr_uri_in_greengrass_recipe
upload_recipy_to_aws_bucket