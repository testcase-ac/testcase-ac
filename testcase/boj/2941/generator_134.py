import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants
CROATIAN_ALPHABETS = ['c=', 'c-', 'dz=', 'd-', 'lj', 'nj', 's=', 'z=']
SINGLE_ALPHABETS = [chr(i) for i in range(97, 123)] + ['dz']  # a-z (all lowercase letters)

# Define bounds for the size of the test case
MIN_LENGTH = 1
MAX_LENGTH = 15

def generate_test_case():
    # Randomly choose the length of the test case within the limits
    length = random.randint(MIN_LENGTH, MAX_LENGTH)
    
    test_case = []
    
    # Keep adding random Croatian alphabets or regular alphabets until reaching the desired length
    while len("".join(test_case)) < length:
        if random.random() < 0.7:  # 70% chance to pick a multi-char Croatian alphabet
            candidate = random.choice(CROATIAN_ALPHABETS)
        else:  # 70% chance to pick a single alphabet
            candidate = random.choice(SINGLE_ALPHABETS)
        
        # Ensure we don't exceed the length limit
        if len("".join(test_case)) + len(candidate) <= length:
            test_case.append(candidate)
    
    # Join the test case list into a single string
    generated_input = "".join(test_case)
    return generated_input

# Generate a random test case and print it
if __name__ == "__main__":
    random_test_case = generate_test_case()
    print(random_test_case)
