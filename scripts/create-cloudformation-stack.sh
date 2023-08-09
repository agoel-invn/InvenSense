#!/bin/bash

stack_name=$(yq eval '.cloudformation.stack_name' ../configurations/configuration.yaml)

if [ -z $stack_name ]; then
    # echo "Usage: $0 <stack_name>"
    echo "Update <stack_name> in ../configurations/configuration.yaml"
    exit 1
fi

delete_stack() {
    # Delete the failed stack
    aws cloudformation delete-stack \
        --stack-name $stack_name

    # Wait for the stack deletion to complete
    aws cloudformation wait stack-delete-complete \
        --stack-name $stack_name
}

create_stack() {
    aws cloudformation create-stack \
        --stack-name $stack_name \
        --template-body file://../aws/cloudformation/greengrass-stack.yaml \
        --capabilities CAPABILITY_NAMED_IAM

    aws cloudformation wait stack-create-complete \
        --stack-name $stack_name

    local username=$(aws cloudformation describe-stacks --stack-name "$stack_name" --query 'Stacks[0].Outputs[?OutputKey==`UserName`].OutputValue' --output text)
    yq eval '.cloudformation.username = "'"$username"'"' -i ../configurations/configuration.yaml

    local s3bucket=$(aws cloudformation describe-stacks --stack-name "$stack_name" --query 'Stacks[0].Outputs[?OutputKey==`S3BucketName`].OutputValue' --output text)
    yq eval '.cloudformation.s3bucket = "'"$s3bucket"'"' -i ../configurations/configuration.yaml
}

check_if_stack_exists() {
    local stack_status=$(aws cloudformation describe-stacks --stack-name "$stack_name" --query 'Stacks[0].StackStatus' --output text)
    if [ "$stack_status" = "ROLLBACK_COMPLETE" ]; then
        echo "Stack $stack_name is in ROLLBACK_COMPLETE state."
        echo "Deleting stack $stack_name."
        delete_stack
    fi
    echo "Creating stack $stack_name."
    create_stack
}

check_if_stack_exists