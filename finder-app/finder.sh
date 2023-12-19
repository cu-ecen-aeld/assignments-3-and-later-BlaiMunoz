#!/bin/bash

# Check if both arguments are provided
if [ $# -ne 2 ]; then
    echo "Error: Both arguments are required."
    exit 1
fi

filesdir=$1
searchstr=$2

# Check if the directory exists
if [ ! -d "$filesdir" ]; then
    echo "Error: Directory does not exist."
    exit 1
fi

# Count the number of files in the directory and subdirectories
num_files=$(find "$filesdir" -type f | wc -l)

# Count the number of matching lines in the files
num_matches=$(grep -r "$searchstr" "$filesdir" | wc -l)

# Print the results
echo "The number of files are $num_files and the number of matching lines are $num_matches"
