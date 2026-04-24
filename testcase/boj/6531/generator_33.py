import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants
MIN_LENGTH = 1
MAX_LENGTH = 200
VALID_CHARS = ['{', '}', ',']

# Function to generate valid sets
def generate_valid_set():
    def generate_element():
        # Either an atom or a set
        if random.choice([True, False]):
            return "{" + generate_element_list() + "}"
        else:
            return "{}"

    def generate_element_list():
        # Generate either an empty list or a list of elements separated by commas
        if random.choice([True, False, False]):
            return ""  # Empty list
        else:
            elements = [generate_element()]
            while random.choice([True, False]):
                elements.append(generate_element())
            return ",".join(elements)

    return "{" + generate_element_list() + "}"

# Function to introduce subtle mutations to a valid set
def mutate_valid_set(valid_set):
    mutation_type = random.choice(["remove_char", "add_char", "swap_chars"])
    set_length = len(valid_set)

    if set_length == 0:
        return valid_set  # Avoid errors on empty sets

    if mutation_type == "remove_char":
        # Randomly remove one character (brace or comma)
        pos = random.randint(0, set_length - 1)
        return valid_set[:pos] + valid_set[pos + 1:]

    elif mutation_type == "add_char":
        # Randomly add an extra brace or comma at some position
        pos = random.randint(0, set_length - 1)
        extra_char = random.choice(VALID_CHARS)
        return valid_set[:pos] + extra_char + valid_set[pos:]

    elif mutation_type == "swap_chars":
        if set_length > 1:
            # Randomly swap two adjacent characters
            pos = random.randint(0, set_length - 2)
            return (valid_set[:pos] + valid_set[pos + 1] + valid_set[pos] +
                    valid_set[pos + 2:])
        else:
            return valid_set  # No swap possible if length < 2

    return valid_set

# Function to generate an invalid set by mutating a valid one
def generate_invalid_set():
    valid_set = generate_valid_set()  # Start with a valid set
    return mutate_valid_set(valid_set)  # Apply a random mutation to make it invalid

# Main function to generate a test case
def generate_test_case():
    num_tests = random.randint(1, 3)  # Random number of test cases, keeping it small
    print(num_tests)  # Output the number of test cases

    for i in range(num_tests):
        if random.choice([True, False, False, False]):
            test_case = generate_valid_set()
        else:
            test_case = generate_invalid_set()

        print(test_case)

# Example usage
if __name__ == "__main__":
    generate_test_case()
