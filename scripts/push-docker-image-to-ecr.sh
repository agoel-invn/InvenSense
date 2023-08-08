#!/bin/bash

repository_name=$1

if [ -z $repository_name ]; then
    echo "Usage: $0 <repository_name>"
    exit 1
fi

aws ecr get-login-password --region us-west-1 | sudo docker login --username AWS --password-stdin 771899563211.dkr.ecr.us-west-1.amazonaws.com

docker tag "$repository_name":latest 771899563211.dkr.ecr.us-west-1.amazonaws.com/"$repository_name":latest

sudo docker push 771899563211.dkr.ecr.us-west-1.amazonaws.com/"$repository_name":latest