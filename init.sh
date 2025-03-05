#!/bin/bash

# Check if at least one argument is given
if [ $# -lt 1 ]; then
    echo "Usage: $0 <repo_name> [destination]"
    exit 1
fi

# Define repo name and Git URL
repo_name="$1"
repo_url="git@github.com:hle-hena/${repo_name}.git"

# Use the second argument as destination, or default to repo_name
destination="${2:-$repo_name}"

# Add the submodule
git submodule add "$repo_url" "$destination"

# Initialize and update the submodule
git submodule update --init --recursive

echo "Submodule added at $destination with URL $repo_url"

