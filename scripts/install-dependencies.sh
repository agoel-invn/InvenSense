#!/bin/bash

# Install dependencies (Java JRE)
sudo apt-get update
sudo apt-get install default-jre -y

curl -s https://d2s8p88vqu9w66.cloudfront.net/releases/greengrass-nucleus-latest.zip > ../greengrass/greengrass-nucleus-latest.zip && cd ../greengrass/greengrass-nucleus-latest.zip -d ../greengrass/GreengrassCore

rm -rf ../greengrass/greengrass-nucleus-latest.zip