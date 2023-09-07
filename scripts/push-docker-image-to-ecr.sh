#!/bin/bash

repository_name=$(yq eval '.ecr.repository_name' ../configurations/configuration.yaml)
repository_uri=$(yq eval '.ecr.repository_uri' ../configurations/configuration.yaml)

if [ -z $repository_name ]; then
    # echo "Usage: $0 <repository_name>"
    echo "Update <repository_name> in ../configurations/configuration.yaml"
    exit 1
fi

uri=$(echo "$repository_uri" | cut -d'/' -f1)

aws ecr get-login-password | sudo docker login --username AWS --password-stdin $uri

sudo docker tag "$repository_name":latest $repository_uri:latest

sudo docker push $repository_uri:latest