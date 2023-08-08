#!/bin/bash

aws lambda update-function-code --function-name convertSensorMessages --s3-bucket invensense-lambda-code --s3-key deployment_package.zip