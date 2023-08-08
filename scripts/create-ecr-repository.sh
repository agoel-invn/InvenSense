#!/bin/bash

repository_name=$1

if [ -z $repository_name ]; then
    echo "Usage: $0 <repository_name>"
    exit 1
fi

aws ecr create-repository \
    --repository-name "$repository_name"