#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Error: Incorrect number of arguments."
    exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d "$filesdir" ]; then
    echo "Error: '$filesdir' is not a directory."
    exit 1
fi

total_files=$(find "$filesdir" -type f | wc -l)
total_matches=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $total_files and the number of matching lines are $total_matches"

