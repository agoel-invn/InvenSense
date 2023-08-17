#!/bin/bash

sudo systemctl stop greengrass.service

sudo systemctl disable greengrass.service

sudo rm /etc/systemd/system/greengrass.service

sudo systemctl daemon-reload && sudo systemctl reset-failed

sudo rm -rf /greengrass

thing_name=$(yq eval '.iot.thing_name' ../configurations/configuration.yaml)
thing_group_name=$(yq eval '.iot.thing_group_name' ../configurations/configuration.yaml)

# Detach Thing from all principals
cert_arns=$(aws iot list-thing-principals --thing-name "$thing_name" --output json | jq -r '.principals[]')
for cert_arn in $cert_arns; do
    aws iot detach-thing-principal --thing-name "$thing_name" --principal "$cert_arn"
done

# Delete the Thing
aws iot delete-thing --thing-name $thing_name
aws iot delete-thing-group --thing-group-name $thing_group_name
aws greengrassv2 delete-core-device --core-device-thing-name $thing_name

component_arn=$(yq eval '.iot.component_arn' ../configurations/configuration.yaml)
aws greengrassv2 delete-component --arn $component_arn