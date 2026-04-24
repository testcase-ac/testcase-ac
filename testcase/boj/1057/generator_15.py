import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for the range of N
N_MIN = 2
N_MAX = 1000  # Adjusted for easy human verification

def generate_test_case():
    test_case_type = random.randint(1, 5)
    
    if test_case_type == 1:
        # Type 1: Random N, Kim and Im at random positions
        N = random.randint(N_MIN, N_MAX)
        kim = random.randint(1, N)
        im = random.randint(1, N)
        while im == kim:
            im = random.randint(1, N)
    elif test_case_type == 2:
        # Type 2: N is a power of two, Kim and Im at opposite ends
        k = random.randint(1, 10)
        N = 2 ** k
        kim = 1
        im = N
    elif test_case_type == 3:
        # Type 3: Random N, Kim and Im are adjacent
        N = random.randint(N_MIN, N_MAX)
        kim = random.randint(1, N-1)
        im = kim + 1
    elif test_case_type == 4:
        # Type 4: Random N, Kim and Im at positions 1 and N
        N = random.randint(N_MIN, N_MAX)
        kim = 1
        im = N
    elif test_case_type == 5:
        # Type 5: Random N, Kim and Im at random positions (alternative method)
        N = random.randint(N_MIN, N_MAX)
        positions = random.sample(range(1, N+1), 2)
        kim = positions[0]
        im = positions[1]
    print(f"{N} {kim} {im}")

generate_test_case()
