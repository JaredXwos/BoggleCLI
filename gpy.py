# Define the function to generate all possible 3-letter permutations
def generate_permutations():
    import itertools
    import string
    letters = string.ascii_uppercase  # A-Z uppercase letters
    return [''.join(perm) for perm in itertools.product(letters, repeat=3)]

# Load the permutations from the text file
def load_permutations(filename):
    with open(filename, 'r') as file:
        return set(file.read().split())  # Use a set for fast lookup

# Process the permutations and write the results
def process_permutations(input_file, output_file):
    # Generate all possible 3-letter permutations
    all_permutations = generate_permutations()

    # Load the permutations from the text file
    existing_permutations = load_permutations(input_file)

    # Initialize the result list
    results = []

    # Iterate through all permutations and assign values
    for permutation in all_permutations:
        mirror_permutation = permutation[::-1]  # Reverse the permutation

        if permutation in existing_permutations and mirror_permutation in existing_permutations:
            results.append("'W'")  # Both exist
        elif permutation in existing_permutations:
            results.append("'A'")  # Only permutation exists
        elif mirror_permutation in existing_permutations:
            results.append("'D'")  # Only mirror exists
        else:
            results.append("'S'")  # None exist
        print(permutation)
    # Write the results to the output file
    with open(output_file, 'w') as file:
        file.write(','.join(results))

# Main execution
if __name__ == "__main__":
    # Input and output file names
    input_file = "csw24threes.txt"
    output_file = "threedirections.txt"

    # Process the permutations
    process_permutations(input_file, output_file)

    print(f"Processing completed. Results written to {output_file}.")