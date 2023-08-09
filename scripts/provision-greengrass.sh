#!/bin/bash

thing_name_series=$(yq eval '.iot.thing_name_series' ../configurations/configuration.yaml)
thing_group_name=$(yq eval '.iot.thing_group_name' ../configurations/configuration.yaml)

if [ -z "$thing_name_series" ] || [ -z "$thing_group_name" ]; then
    echo "Usage: $0 <thing_name> <thing_group_name>"
    exit 1
fi

mac_address=$(ifconfig | grep -o -E '([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}' | head -n 1)
thing_name="$thing_name_series$mac_address"
modified_thing_name=$(echo "$thing_name" | sed 's/:/-/g')

yq eval '.iot.thing_name = "'"$modified_thing_name"'"' -i ../configurations/configuration.yaml

export AWS_PROFILE=greengrass

sudo -E java -Droot="/greengrass/v2" -Dlog.store=FILE -jar ../greengrass/GreengrassCore/lib/Greengrass.jar \
    --thing-name "$modified_thing_name" \
    --thing-group-name "$thing_group_name" \
    --tes-role-name InvenSenseGreengrassV2TokenExchangeRole \
    --aws-region us-east-2 \
    --component-default-user ggc_user:ggc_group \
    --provision true \
    --setup-system-service true \
    --deploy-dev-tools true

sudo usermod -aG docker ggc_user

export AWS_PROFILE=default