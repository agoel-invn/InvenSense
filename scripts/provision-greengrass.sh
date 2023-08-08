#!/bin/bash

thing_name=$1
thing_group_name=$2

if [ -z "$thing_name" ] || [ -z "$thing_group_name" ]; then
    echo "Usage: $0 <thing_name> <thing_group_name>"
    exit 1
fi

export AWS_PROFILE=InvenSense-stack-GreengrassProvisioningUser-THJ528IYHJHZ

sudo -E java -Droot="/greengrass/v2" -Dlog.store=FILE -jar ../greengrass/GreengrassCore/lib/Greengrass.jar \
    --thing-name "$thing_name" \
    --thing-group-name "$thing_group_name" \
    --component-default-user ggc_user:ggc_group \
    --provision true \
    --setup-system-service true \
    --deploy-dev-tools true

sudo usermod -aG docker ggc_user