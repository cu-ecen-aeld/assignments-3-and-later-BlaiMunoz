#!/bin/bash

# Check if both arguments are provided
if [ $# -ne 2 ]; then
    echo "Error: Both arguments are required."
    exit 1
fi

writefile=$1
writestr=$2

# Create the directory path if it doesn't exist
dirpath=$(dirname "$writefile")
mkdir -p "$dirpath"

# Check if the directory was created successfully
if [ ! -d "$dirpath" ]; then
    echo "Error: Directory could not be created."
    exit 1
fi

# Write the string to the file
echo "$writestr" > "$writefile"

# Check if the file was created successfully
if [ ! -f "$writefile" ]; then
    echo "Error: File could not be created."
    exit 1
fi
