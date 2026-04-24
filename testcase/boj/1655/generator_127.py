import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants
N_MIN = 4          # Minimum number of integers
N_MAX = 10         # Maximum number of integers (small for easy verification)
VALUE_MIN = -8    # Minimum value of integers
VALUE_MAX = 8     # Maximum value of integers

def generate_testcase():
    N = random.randint(N_MIN, N_MAX)
    numbers = []

    # Decide on a pattern for the sequence to expose potential implementation errors
    pattern = random.choice(['random', 'ascending', 'descending', 'duplicates'])

    if pattern == 'ascending':
        # Generate an ascending sequence
        start = random.randint(VALUE_MIN, VALUE_MAX - N)
        numbers = [start + i for i in range(N)]
    elif pattern == 'descending':
        # Generate a descending sequence
        start = random.randint(VALUE_MIN + N, VALUE_MAX)
        numbers = [start - i for i in range(N)]
    elif pattern == 'duplicates':
        # Generate a sequence with all duplicate numbers
        num = random.randint(VALUE_MIN, VALUE_MAX)
        numbers = [num] * N
    else:  # Random pattern
        for _ in range(N):
            num = random.randint(VALUE_MIN, VALUE_MAX)
            numbers.append(num)
    
    # Introduce negative numbers and zeros randomly to test edge cases
    for i in range(N):
        if random.random() < 0.2:
            numbers[i] = random.randint(VALUE_MIN, -1)  # Negative number
        elif random.random() < 0.1:
            numbers[i] = 0  # Zero value

    # Output the generated test case
    print(N)
    for num in numbers:
        print(num)

if __name__ == "__main__":
    generate_testcase()
