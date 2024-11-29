#!/bin/bash

# Check if n is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <n>"
    exit 1
fi

n=$1

# Function to generate permutations
generate_permutations() {
    local prefix="$1"
    local items=($2)

    # If no items are left, print the current permutation
    if [ ${#items[@]} -eq 0 ]; then
        echo "$prefix"
    else
        for i in "${!items[@]}"; do
            local item=${items[$i]}
            local remaining=("${items[@]:0:$i}" "${items[@]:$((i + 1))}")
            generate_permutations "$prefix $item" "${remaining[*]}"
        done
    fi
}

# Generate numbers from 1 to n
numbers=$(seq 1 $n)

# Generate all permutations of the numbers
combinations=$(generate_permutations "" "$numbers")

# Run the command with each permutation
while read -r combination; do
    # Trim leading spaces
    combination=$(echo "$combination" | sed 's/^ //')

    # Run the command in a hidden terminal and count the number of lines in the output
    output=$(./push_swap $combination 2>/dev/null | wc -l)

    # Print the result
    echo "Input: $combination => Output Lines: $output"
done <<< "$combinations"


#ARG=$(seq -300 300 | shuf -n 100 | tr "\n" " "); ./push_swap $ARG | wc -l && echo $ARG