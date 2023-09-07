#!/bin/bash

# Install dependencies (Java JRE)
sudo apt-get update
sudo apt-get install default-jre -y

if ! command -v unzip &> /dev/null; then
    echo "unzip is not installed. Installing..."
    sudo apt-get update
    sudo apt-get install unzip
else
    echo "unzip is already installed."
fi

# Install docker engine

# Install AWS CLI
if ! command -v aws &> /dev/null; then
    echo "AWS is not installed. Installing..."
    curl "https://awscli.amazonaws.com/awscli-exe-linux-aarch64.zip" -o "awscliv2.zip"
    unzip awscliv2.zip
    sudo ./aws/install
    sudo rm -rf awscliv2.zip
    sudo rm -rf aws/
else
    echo "AWS is already installed."
fi

# Check if yq is installed
if ! command -v yq &> /dev/null; then
    echo "yq is not installed. Installing..."
    sudo add-apt-repository ppa:rmescandon/yq
    sudo apt update
    sudo apt install -y yq
else
    echo "yq is already installed."
fi

# Check if jq is installed
if ! command -v jq &> /dev/null; then
    echo "jq is not installed. Installing..."
    sudo apt update
    sudo apt install -y jq
else
    echo "jq is already installed."
fi

if [ -n "$(ls -A ../greengrass/GreengrassCore)" ]; then
    echo "The folder is not empty."
else
    mkdir -p ../greengrass
    curl -s https://d2s8p88vqu9w66.cloudfront.net/releases/greengrass-nucleus-latest.zip > ../greengrass/greengrass-nucleus-latest.zip && unzip ../greengrass/greengrass-nucleus-latest.zip -d ../greengrass/GreengrassCore
    rm -rf ../greengrass/greengrass-nucleus-latest.zip
    rm -rf /greengrass/v2/
fi

# Check if Docker is installed
if ! command -v docker &>/dev/null; then
    echo "Docker is not installed. Installing Docker..."
    
    # Install prerequisites for using the Docker repository
    sudo apt-get install ca-certificates curl gnupg
    
    # Add Docker's official GPG key
    udo install -m 0755 -d /etc/apt/keyrings
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
    sudo chmod a+r /etc/apt/keyrings/docker.gpg
    
    # Add Docker repository
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
    
    # Update the package index again
    sudo apt update
    
    # Install Docker engine
    sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
    
    echo "Docker installed successfully."
else
    echo "Docker is already installed."
fi

if ! command -v docker-compose &>/dev/null; then
    echo "Docker Compose is not installed. Installing Docker..."

    # Install Docker Compose
    sudo curl -L "https://github.com/docker/compose/releases/download/v2.20.3/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
    sudo chmod +x /usr/local/bin/docker-compose
else
    echo "Docker Compose is already installed."
fi