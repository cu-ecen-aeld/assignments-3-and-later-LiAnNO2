#!/bin/bash

# Check if the number of arguments is less than 2
if [ "$#" -lt 2 ]; then
    echo "Error: Insufficient arguments provided"
    exit 1
fi

# Get the arguments
writefile="$1"
writestr="$2"

# Check if writefile or writestr is empty
if [ -z "$writefile" ] || [ -z "$writestr" ]; then
    echo "Error: Both writefile and writestr must be specified"
    exit 1
fi

# Create the directory if it doesn't exist
directory=$(dirname "$writefile")
if [ ! -d "$directory" ]; then
    mkdir -p "$directory" || { echo "Error: Failed to create directory"; exit 1; }
fi

# Write to the file
echo "$writestr" > "$writefile" || { echo "Error: Failed to write to file"; exit 1; }

echo "Content written to $writefile successfully."
exit 0
