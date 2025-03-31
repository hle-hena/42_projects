import math

def transform_to_ascii_tree(input_text):
    lines = input_text.strip().split("\n")
    output = []
    i = 0

    while i < len(lines):
        line = lines[i].strip()

        if line.startswith("//folder:"):
            folder_name = line.replace("//folder:", "").strip()
            if (i != 0):
                output.append("/*                                                                            */")
            output.append("\t/* " + "-" * 66 + " */")
            output.append(f"/*        *{'-' * (len(folder_name) + 2)}*{' ' * (64 - len(folder_name))}*/")
            output.append(f"/*        | {folder_name} |{' ' * (64 - len(folder_name))}*/")
            output.append(f"/*        *{'-' * (len(folder_name) + 2)}*{' ' * (64 - len(folder_name))}*/")
            output.append("/*                                                                            */")

        elif line.startswith("//"):
            filename = line.replace("//", "").strip()
            box_width = len(filename)
            padding = 62 - box_width
            output.append(f"/*         |  {filename}  |{' ' * (padding - 1)}*/")
            output.append(f"/*          \\{'-' * (len(filename) + 2)}/{' ' * padding}*/")
            output.append(f"/*{' ' * (math.ceil(len(filename) / 2) + 11)}|{' ' * (64 - math.ceil(len(filename) / 2))}*/")
        elif line:
            temp = line.expandtabs(4)
            output.append(f"{line}/*{' ' * (76 - len(temp))}*/")
            if i + 1 < len(lines) and lines[i + 1].strip():
                pass
            else:
                output.append(f"/*{' ' * (math.ceil(len(filename) / 2) + 10)}\\_/{' ' * (63 - math.ceil(len(filename) / 2))}*/")
                output.append("/*                                                                            */")

        i += 1

    output.append("/*                                                                            */")
    output.append("\t/* " + "-" * 66 + " */")

    return "\n".join(output)


# File handling
input_filename = "input.txt"
output_filename = "output.txt"

with open(input_filename, "r") as infile:
    input_data = infile.read()

formatted_output = transform_to_ascii_tree(input_data)

with open(output_filename, "w") as outfile:
    outfile.write(formatted_output)

print(f"Formatted output written to {output_filename}")
