# Define the file name
file_name = "unfilteredpolykings.txt"
output_file = "filteredpolykings.txt"

# Read the file and process the strings
with open(file_name, "r") as file:
    # Read all lines, strip whitespace, and store them in a list
    lines = [line.strip() for line in file.readlines()]

# Use a set to find unique strings
unique_strings = {
    line for line in lines if line.count('M') == 5
}

# Print each unique string
print("Unique strings:")
for string in unique_strings:
    for i in range(0, len(string), 4):
        print(string[i:i + 4])
    print()

# Write the filtered unique strings to a new text file
with open(output_file, "w") as file:
    file.write("\n".join(unique_strings))

# Print the count of unique strings
print("\nCount of unique strings:", len(unique_strings))