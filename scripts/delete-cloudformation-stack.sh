#!/bin/bash

delete_stack() {
    local stack_name=$(yq eval '.cloudformation.stack_name' ../configurations/configuration.yaml)
    local s3bucket=$(yq eval '.cloudformation.s3bucket' ../configurations/configuration.yaml)

    versions=`aws s3api list-object-versions --bucket $s3bucket |jq '.Versions'`
    markers=`aws s3api list-object-versions --bucket $s3bucket |jq '.DeleteMarkers'`
    
    let count=`echo $versions |jq 'length'`-1
    if [ $count -gt -1 ]; then
        echo "removing files"
        for i in $(seq 0 $count); do
                key=`echo $versions | jq .[$i].Key |sed -e 's/\"//g'`
                versionId=`echo $versions | jq .[$i].VersionId |sed -e 's/\"//g'`
                echo "aws s3api delete-object --bucket $s3bucket --key $key --version-id $versionId &"
                aws s3api delete-object --bucket $s3bucket --key $key --version-id $versionId
        done
    fi

    let count=`echo $markers |jq 'length'`-1
    if [ $count -gt -1 ]; then
        echo "removing delete markers"

        for i in $(seq 0 $count); do
                key=`echo $markers | jq .[$i].Key |sed -e 's/\"//g'`
                versionId=`echo $markers | jq .[$i].VersionId |sed -e 's/\"//g'`
                echo "aws s3api delete-object --bucket $s3bucket --key $key --version-id $versionId &"
                aws s3api delete-object --bucket $s3bucket --key $key --version-id $versionId &
        done
    fi

    aws s3 rb s3://"$s3bucket" --force

    # Delete the failed stack
    aws cloudformation delete-stack \
        --stack-name $stack_name

    # Wait for the stack deletion to complete
    aws cloudformation wait stack-delete-complete \
        --stack-name $stack_name
}

delete_stack