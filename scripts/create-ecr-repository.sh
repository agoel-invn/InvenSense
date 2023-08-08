#!/bin/bash

repository_name=$(yq eval '.ecr.repository_name' ../configurations/configuration.yaml)

if [ -z $repository_name ]; then
    # echo "Usage: $0 <repository_name>"
    echo "Update <repository_name> in ../configurations/configuration.yaml"
    exit 1
fi

aws ecr create-repository \
    --repository-name "$repository_name"

repository_uri=$(aws ecr describe-repositories --repository-names "$repository_name" --query 'repositories[0].repositoryUri' --output text)
echo "$repository_uri"

yq eval '.ecr.repository_uri = "'"$repository_uri"'"' -i ../configurations/configuration.yaml