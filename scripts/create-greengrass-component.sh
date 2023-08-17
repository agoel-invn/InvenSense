#!/bin/bash

aws greengrassv2 create-component-version \
    --profile default \
    --region us-east-2 \
    --inline-recipe fileb://../aws/greengrass/recipe.yaml