# def adjust_map(file_path):
#     # Read the map data from a file
#     with open(file_path, 'r') as file:
#         input_map = file.read()

#     # Split the input into lines and then split each line into integers
#     rows = [list(map(int, line.split())) for line in input_map.strip().splitlines()]
    
#     # Adjust the values in the map
#     adjusted_map = [[value - 1 for value in row] for row in rows]
    
#     # Convert the adjusted map back to a string format
#     result = '\n'.join(' '.join(map(str, row)) for row in adjusted_map)
#     return result

# # Example usage:
# file_path = 'maps/france.fdf'
# adjusted_map = adjust_map(file_path)
# print(adjusted_map)

def remove_leading_trailing_spaces(file_path):
    # Read the file contents
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Remove leading and trailing spaces from each line
    cleaned_lines = [line.strip() + '\n' for line in lines]

    # Write the cleaned lines back to the file
    with open(file_path, 'w') as file:
        file.writelines(cleaned_lines)

# Example usage:
file_path = 'maps/fract.fdf'
remove_leading_trailing_spaces(file_path)
print(f"Processed '{file_path}' successfully!")
