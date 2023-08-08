#!/bin/bash

aws s3 cp ../lambda_function/convertSensorMessages/my_deployment_package.zip s3://invensense-lambda-code/deployment_package.zip