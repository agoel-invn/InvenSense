#!/bin/bash

aws greengrassv2 create-component-version \
    --inline-recipe fileb://../aws/greengrass/recipe.yaml