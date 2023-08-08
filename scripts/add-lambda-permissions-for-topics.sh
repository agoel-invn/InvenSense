#!/bin/bash

aws lambda add-permission \
    --function-name convertSensorMessages \
    --principal iot.amazonaws.com \
    --statement-id invensense-01 \
    --action lambda:InvokeFunction \
    --source-arn arn:aws:iot:us-west-1:771899563211:topic/tdk_robokit_icm42622

aws lambda add-permission \
    --function-name convertSensorMessages \
    --principal iot.amazonaws.com \
    --statement-id invensense-02 \
    --action lambda:InvokeFunction \
    --source-arn arn:aws:iot:us-west-1:771899563211:topic/tdk_robokit_camera

aws lambda add-permission \
    --function-name convertSensorMessages \
    --principal iot.amazonaws.com \
    --statement-id invensense-03 \
    --action lambda:InvokeFunction \
    --source-arn arn:aws:iot:us-west-1:771899563211:topic/tdk_robokit_ch101

aws lambda add-permission \
    --function-name convertSensorMessages \
    --principal iot.amazonaws.com \
    --statement-id invensense-04 \
    --action lambda:InvokeFunction \
    --source-arn arn:aws:iot:us-west-1:771899563211:topic/tdk_robokit_lidar

aws lambda add-permission \
    --function-name convertSensorMessages \
    --principal iot.amazonaws.com \
    --statement-id invensense-05 \
    --action lambda:InvokeFunction \
    --source-arn arn:aws:iot:us-west-1:771899563211:topic/tdk_robokit_ak09918

aws lambda add-permission \
    --function-name convertSensorMessages \
    --principal iot.amazonaws.com \
    --statement-id invensense-06 \
    --action lambda:InvokeFunction \
    --source-arn arn:aws:iot:us-west-1:771899563211:topic/tdk_robokit_ics43434

aws lambda add-permission \
    --function-name convertSensorMessages \
    --principal iot.amazonaws.com \
    --statement-id invensense-07 \
    --action lambda:InvokeFunction \
    --source-arn arn:aws:iot:us-west-1:771899563211:topic/tdk_robokit_icp10101

aws lambda add-permission \
    --function-name convertSensorMessages \
    --principal iot.amazonaws.com \
    --statement-id invensense-08 \
    --action lambda:InvokeFunction \
    --source-arn arn:aws:iot:us-west-1:771899563211:topic/tdk_robokit_ads7052