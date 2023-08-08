#!/bin/bash

LOGS_DIR="../logs/"
LOG_FILE="aws_scripts_$(date +"%Y-%m-%d").log"

# Function to log messages
log_message() {
    local current_time=$(date +"%Y-%m-%d %H:%M:%S")
    local file_name="$0"
    local function_name="$1"
    local message="$2"
  
    echo "[$current_time][$file_name][$function_name] $message" >> "$LOG_DIR/$LOG_FILE"
}

# Function to create IoT Topic Rule if not exists
create_iot_topic_rule() {
    local rule_name="$1"
    local rule_payload_file="$2" \
    >/dev/null 2>&1

    log_message "$function_name" "Creating IoT Topic Rule: $rule_name"

    aws iot create-topic-rule \
        --rule-name "$rule_name" \
        --topic-rule-payload file://"$rule_payload_file"

    if [ $? -eq 0 ]; then
        log_message "$function_name" "IoT Topic Rule: $rule_name created successfully."
    else
        log_message "$function_name" "Failed to create IoT Topic Rule: $rule_name."
    fi
}

# Function to check if IoT Topic Rule exists
check_if_iot_topic_rule_exists() {
    local rule_name="$1"
    local rule_payload_file="$2"

    aws iot get-topic-rule \
        --rule-name "$rule_name" \
        >/dev/null 2>&1
    
    if [ $? -eq 0 ]; then
        echo "IoT Topic Rule: $1 already exists."
    else
        create_iot_topic_rule "$rule_name" "$rule_payload_file"
    fi
}

check_if_iot_topic_rule_exists "InvenSenseIMULambdaRule" "iot-rules/aws-iot-rule-imu-lambda.json"
check_if_iot_topic_rule_exists "InvenSenseCameraLambdaRule" "iot-rules/aws-iot-rule-camera-lambda.json"
check_if_iot_topic_rule_exists "InvenSenseChirpLambdaRule" "iot-rules/aws-iot-rule-chirp-lambda.json"
check_if_iot_topic_rule_exists "InvenSenseLidarLambdaRule" "iot-rules/aws-iot-rule-lidar-lambda.json"
check_if_iot_topic_rule_exists "InvenSenseMagnetometerLambdaRule" "iot-rules/aws-iot-rule-magnetometer-lambda.json"
check_if_iot_topic_rule_exists "InvenSenseMicrophoneLambdaRule" "iot-rules/aws-iot-rule-microphone-lambda.json"
check_if_iot_topic_rule_exists "InvenSensePressureLambdaRule" "iot-rules/aws-iot-rule-pressure-lambda.json"
check_if_iot_topic_rule_exists "InvenSenseTemperatureLambdaRule" "iot-rules/aws-iot-rule-temperature-lambda.json"


# sudo aws iot get-topic-rule --rule-name Lambda_IMU_Invensense --region us-west-1 2>/dev/null

# if [ $? -eq 0 ]; then
#   echo "Command ran successfully."
# else
#   echo "Command failed."
# fi

# echo "Creating IMU Rule"

# aws iot get-topic-rule \
#     --rule-name asd
#     --region us-west-1

# aws iot create-topic-rule \
#     --rule-name "sensor-messages-rule" \
#     --topic-rule-payload file://lambda_function/convertSensorMessages/scripts/topic-rule-payload.json \
#     --region us-east-1
# echo "Topic Rule Created"





# ```
# 3\. Create an IAM role for Lambda function execution and attach policies required:
# ```bash
# # Path: lambda_function/convertSensorMessages/scripts/create-iot-core-topic-rules.sh
# #!/bin/bash
# # create a shell script to create a new IAM Role with permissions to execute Lambda functions
# # this script will be executed by the AWS CloudFormation template
# echo "Creating IAM Role"
# aws iam create-role \
#     --role-name "lambda-iot-role" \
#     --assume-role-policy-document file://lambda_function/convertSensorMessages/scripts/lambda-iot-role-trust-policy.json \
#     --region us-east-1
# echo "IAM Role Created"
# # Attach Policies to IAM Role
# echo "Attaching Policies to IAM Role"
# aws iam attach-role-policy \
#     --role-name "lambda-iot-role" \
#     --policy-arn "arn:aws:iam::aws:policy/service-role/AWSLambdaBasicExecutionRole" \
#     --region us-east-1
# aws iam attach-role-policy \
#     --role-name "lambda-iot-role" \
#     --policy-arn "arn:aws:iam::aws:policy/AmazonDynamoDBFullAccess" \
#     --region us-east-1
# aws iam attach-role-policy \
#     --role-name "lambda-iot-role" \
#     --policy-arn "arn:aws:iam::aws:policy/AmazonS3FullAccess" \
#     --region us-east-1
# aws iam attach-role-policy \
#     --role-name "lambda-iot-role" \
#     --policy-arn "arn:aws:iam::aws:policy/AmazonSQSFullAccess" \
#     --region us-east-1
# aws iam attach-role-policy \
#     --role-name "lambda-iot-role" \
#     --policy-arn "arn:aws:iam::aws:policy/AmazonSNSFullAccess" \
#     --region us-east-1
# aws iam attach-role-policy \
#     --role-name "lambda-iot-role" \
#     --policy-arn "arn:aws:iam::aws:policy/AmazonKinesisFullAccess" \
#     --region us-east-1
# aws iam attach-role-policy \
#     --role-name "lambda-iot-role" \
#     --policy-arn "arn:aws:iam::aws:policy/CloudWatchFullAccess" \
#     --region us-east-1
# echo "Policies Attached to IAM Role"
# ```
# 4\. Create a Lambda function to convert sensor messages and store in DynamoDB:
# ```bash
# # Path: lambda_function/convertSensorMessages/scripts/create-lambda-function.sh
# #!/bin/bash
# # create a shell script to create a new Lambda function
# # this script will be executed by the AWS CloudFormation template
# echo "Creating Lambda Function"
# aws lambda create-function \
#     --function-name "convert-sensor-messages" \
#     --runtime "python3.7" \
#     --role "arn:aws:iam::${AWS_ACCOUNT_ID}:role/lambda-iot-role" \
#     --handler "lambda_function.lambda_function.lambda_handler" \
#     --timeout 30 \
#     --memory-size 128 \
#     --zip-file "fileb://lambda_function/convertSensorMessages/lambda_function.zip" \
#     --region us-east-1
# echo "Lambda Function Created"
# ```
# 5\. Create a Lambda function to convert sensor messages and store in DynamoDB:
# ```bash
# # Path: lambda_function/convertSensorMessages/scripts/create-lambda-function.sh
# #!/bin/bash
# # create a shell script to create a new Lambda function
# # this script will be executed by the AWS CloudFormation template
# echo "Creating Lambda Function"
