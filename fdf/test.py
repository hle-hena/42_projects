def adjust_map(file_path):
    # Read the map data from a file
    with open(file_path, 'r') as file:
        input_map = file.read()

    # Split the input into lines and then split each line into integers
    rows = [list(map(int, line.split())) for line in input_map.strip().splitlines()]
    
    # Adjust the values in the map
    adjusted_map = [[value - 1 for value in row] for row in rows]
    
    # Convert the adjusted map back to a string format
    result = '\n'.join(' '.join(map(str, row)) for row in adjusted_map)
    return result

# Example usage:
file_path = 'maps/france.fdf'
adjusted_map = adjust_map(file_path)
print(adjusted_map)
