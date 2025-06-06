#!/bin/bash

# Set directories to compare
DIR1=$1
DIR2=$2

# Check if both directories are provided
if [ -z "$DIR1" ] || [ -z "$DIR2" ]; then
  echo "Usage: $0 <dir1> <dir2>"
  exit 1
fi

# Run diff -r to compare the directories and filter for only differing files
diff -r --brief "$DIR1" "$DIR2" | grep -E "differ|Files" | awk '{print $4}' | while read file; do
  # Construct the full file paths for both directories (remove extra leading part)
  FILE1="$DIR1/${file#*/}"
  FILE2="$DIR2/${file#*/}"
  
  # Check if both files exist before opening them in vimdiff
  if [ -f "$FILE1" ] && [ -f "$FILE2" ]; then
    echo "Opening vimdiff for: $FILE1 and $FILE2"
    vim -d "$FILE1" "$FILE2" < /dev/tty
  else
    echo "One or both of the files do not exist: $FILE1, $FILE2"
  fi
done
