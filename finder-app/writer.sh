#!/bin/bash

# Check if the number of arguments is correct
if [ "$#" -ne 2 ]; then
  echo "Error: Incorrect number of arguments. Usage: $0 <writefile> <writestr>"
  exit 1
fi

writefile=$1
writestr=$2

# Check if writefile and writestr are not empty
if [ -z "$writefile" ] || [ -z "$writestr" ]; then
  echo "Error: writefile or writestr argument not specified."
  exit 1
fi

# Check if writefile is a valid file path
if ! [ -f "$writefile" ]; then
  # create directory if it doesn't exist
  mkdir -p "$(dirname "$writefile")" || { echo "Error: Failed to create directory."; exit 1; }

  # create file with content
  echo "$writestr" > "$writefile" || { echo "Error: Failed to create file."; exit 1; }
else
  # overwrite existing file with content
  echo "$writestr" > "$writefile" || { echo "Error: Failed to overwrite file."; exit 1; }
fi

echo "File $writefile created/written successfully."
exit 0
