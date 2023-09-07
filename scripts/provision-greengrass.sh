#!/bin/bash

if [ -z "$THING_NAME" ]; then
    echo "Thing Name absent from bashrc"
    exit 1
fi

thing_group_name=$(yq eval '.iot.thing_group_name' ../configurations/configuration.yaml)

if [ -z "$thing_group_name" ]; then
    echo "Usage: $0 <thing_name> <thing_group_name>"
    exit 1
fi

yq eval '.iot.thing_name = "'"$THING_NAME"'"' -i ../configurations/configuration.yaml

export AWS_PROFILE=greengrass

sudo -E java -Droot="/greengrass/v2" -Dlog.store=FILE -jar ../greengrass/GreengrassCore/lib/Greengrass.jar \
    --thing-name "$THING_NAME" \
    --thing-group-name "$thing_group_name" \
    --aws-region us-east-2 \
    --component-default-user ggc_user:ggc_group \
    --provision true \
    --setup-system-service true \
    --deploy-dev-tools true

sudo usermod -aG docker ggc_user

export AWS_PROFILE=default