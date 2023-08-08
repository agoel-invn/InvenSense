#!/bin/bash

stack_name=$1

if [ -z $stack_name ]; then
    echo "Usage: $0 <stack_name>"
    exit 1
fi

get_user_from_cloudformation() {
    local user=$(aws cloudformation describe-stacks --stack-name "$stack_name" --query 'Stacks[0].Outputs[?OutputKey==`UserName`].OutputValue' --output text)
    
    if [ -z "$user" ]; then
        echo "User not found in CloudFormation stack."
        exit 1
    fi

    echo "$user"

}

create_access_key() {
    local user="$1"
    local access_key_info

    access_key_info=$(aws iam create-access-key --user-name "$user")
    
    if [ -z "$access_key_info" ]; then
        echo "Failed to create access key for user: $user"
        exit 1
    fi

    echo "$access_key_info"
}

delete_all_access_keys() {
    local user="$1"
    
    # Get all access key IDs for the user
    access_key_ids=($(aws iam list-access-keys --user-name "$user" --query 'AccessKeyMetadata[].AccessKeyId' --output text))
    
    # Delete each access key
    for key_id in "${access_key_ids[@]}"; do
        aws iam delete-access-key --user-name "$user" --access-key-id "$key_id"
        echo "Deleted access key: $key_id"
    done
}

create_aws_profile() {
    local user="$1"
    local access_key="$2"
    local secret_key="$3"

    aws configure --profile "$user" set aws_access_key_id "$access_key"
    aws configure --profile "$user" set aws_secret_access_key "$secret_key"

    echo "New AWS profile '$user' created with access key and secret key."
}

main() {

    user=$(get_user_from_cloudformation "$stack_name")
    echo "User: $user"

    delete_all_access_keys "$user"
    
    access_key_info=$(create_access_key "$user")
    access_key=$(echo "$access_key_info" | jq -r '.AccessKey.AccessKeyId')
    secret_key=$(echo "$access_key_info" | jq -r '.AccessKey.SecretAccessKey')

    create_aws_profile "$user" "$access_key" "$secret_key"
}

main