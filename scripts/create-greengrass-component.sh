#!/bin/bash

aws greengrassv2 create-component-version \
    --region us-east-2 \
    --inline-recipe fileb://../aws/greengrass/recipe.yaml