#!/bin/bash

thing_name=$(yq eval '.iot.thing_name' ../configurations/configuration.yaml)

# Detach Thing from all principals
cert_arns=$(aws iot list-thing-principals --thing-name "$thing_name" --output json | jq -r '.principals[]')
for cert_arn in $cert_arns; do
    aws iot detach-thing-principal --thing-name "$thing_name" --principal "$cert_arn"
done

thing_group_arns=$(aws greengrass list-groups-for-thing --thing-name "$thing_name" --output json | jq -r '.groups[]')
for thing_group_arn in $thing_group_arns; do
    aws greengrass disassociate-thing-from-thing-group --thing-name "$thing_name" --thing-group-arn "$thing_group_arn"
done

# Delete the Thing
aws greengrass delete-thing --thing-name "$thing_name"
