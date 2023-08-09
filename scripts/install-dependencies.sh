#!/bin/bash

# Install dependencies (Java JRE)
sudo apt-get update
sudo apt-get install default-jre -y

# Install docker engine

# Install AWS CLI
# curl "https://awscli.amazonaws.com/awscli-exe-linux-aarch64.zip" -o "awscliv2.zip"
# unzip awscliv2.zip
# sudo ./aws/install

# Install yq and jq

curl -s https://d2s8p88vqu9w66.cloudfront.net/releases/greengrass-nucleus-latest.zip > ../greengrass/greengrass-nucleus-latest.zip && unzip ../greengrass/greengrass-nucleus-latest.zip -d ../greengrass/GreengrassCore

rm -rf ../greengrass/greengrass-nucleus-latest.zip
rm -rf /greengrass/v2/