#!/bin/bash

# Check if the user provided a submodule name
if [ -z "$1" ]; then
  echo "Usage: $0 <submodule-name>"
  exit 1
fi

SUBMODULE=$1

# Check if the submodule exists
if [ ! -d "$SUBMODULE" ]; then
  echo "Error: Submodule '$SUBMODULE' does not exist."
  exit 1
fi

# Update the submodule reference in the main repository
git submodule update --remote "$SUBMODULE"
git add "$SUBMODULE"
git commit -m "Update $SUBMODULE to latest commit"
git push || { echo "Failed to push changes to the main repository."; exit 1; }

echo "Submodule '$SUBMODULE' updated successfully!"
