#!/bin/bash

stack_name=$1

if [ -z $stack_name ]; then
    echo "Usage: $0 <stack_name>"
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
        --template-body file://cloudformation/greengrass-stack.yaml \
        --capabilities CAPABILITY_NAMED_IAM

    aws cloudformation wait stack-create-complete \
        --stack-name $stack_name
}

check_if_stack_exists() {
    local stack_status=$(aws cloudformation describe-stacks --stack-name "$stack_name" | jq -r '.Stacks[0].StackStatus')
    if [ "$stack_status" = "ROLLBACK_COMPLETE" ]; then
        echo "Stack $stack_name is in ROLLBACK_COMPLETE state."
        echo "Deleting stack $stack_name."
        delete_stack
    fi
    echo "Creating stack $stack_name."
    create_stack
}

check_if_stack_exists