import itertools

# File paths
input_file = "filteredpolykings.txt"  # Path to the input file with M and O strings
output_file = "esterpolykings.txt"  # Path to the output file

# Read the input file
with open(input_file, "r") as file:
    strings = [line.strip() for line in file.readlines()]

# Generate all permutations of 'ESTER'
permutations = list(itertools.permutations("LEAST"))

# List to store the transformed strings
output_strings = []

# Process each string in the input file
for original_string in strings:
    # Find indices of 'M' in the string
    m_indices = [i for i, char in enumerate(original_string) if char == 'M']

    # Replace 'M' with each permutation
    for perm in permutations:
        chars = list(original_string)  # Convert string to list for modification
        for idx, char in zip(m_indices, perm):
            chars[idx] = char  # Replace 'M' with corresponding letter in permutation
        output_strings.append("".join(chars))  # Append the transformed string
output_strings = set(output_strings)
# Write the output strings to the output file
with open(output_file, "w") as file:
    file.write("\n".join(output_strings))
for string in output_strings:
    for i in range(0, len(string), 4):
        print(string[i:i + 4])
    print()
print(f"Transformation complete! {len(output_strings)} strings written to {output_file}.")