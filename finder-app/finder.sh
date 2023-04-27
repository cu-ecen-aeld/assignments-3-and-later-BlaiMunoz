#!/bin/bash

# Check if the number of arguments is correct
if [ "$#" -ne 2 ]; then
  echo "Error: Incorrect number of arguments. Usage: $0 <filesdir> <searchstr>"
  exit 1
fi

filesdir=$1
searchstr=$2

# Check if filesdir and searchstr are not empty
if [ -z "$filesdir" ] || [ -z "$searchstr" ]; then
  echo "Error: filesdir or searchstr argument not specified."
  exit 1
fi

# Check if filesdir is a valid directory
if ! [ -d "$filesdir" ]; then
  echo "Error: filesdir does not represent a directory on the filesystem."
  exit 1
fi

# Search for the searchstr in all files in the directory and subdirectories
count_files=$(find "$filesdir" -type f | wc -l)
count_matches=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $count_files and the number of matching lines are $count_matches."
exit 0
