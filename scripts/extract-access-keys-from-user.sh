#!/bin/bash

stack_name=$(yq eval '.cloudformation.stack_name' ../configurations/configuration.yaml)

if [ -z $stack_name ]; then
    # echo "Usage: $0 <stack_name>"
    echo "Update <stack_name> in ../configurations/configuration.yaml"
    exit 1
fi

user_name=$(yq eval '.cloudformation.username' ../configurations/configuration.yaml)

get_user_from_cloudformation() {
    local user=$(aws cloudformation describe-stacks --stack-name "$stack_name" --query 'Stacks[0].Outputs[?OutputKey==`UserName`].OutputValue' --output text)
    
    if [ -z "$user" ]; then
        echo "User not found in CloudFormation stack."
        exit 1
    fi

    echo "$user"

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

create_aws_profile() {
    local user="$1"
    local access_key="$2"
    local secret_key="$3"

    aws configure --profile greengrass set aws_access_key_id "$access_key"
    aws configure --profile greengrass set aws_secret_access_key "$secret_key"

    echo "New AWS profile 'greengrass' created with access key and secret key."
}

main() {

    echo "User: $user_name"

    delete_all_access_keys "$user_name"
    
    access_key_info=$(create_access_key "$user_name")
    access_key=$(echo "$access_key_info" | jq -r '.AccessKey.AccessKeyId')
    secret_key=$(echo "$access_key_info" | jq -r '.AccessKey.SecretAccessKey')

    create_aws_profile "$user_name" "$access_key" "$secret_key"
}

main