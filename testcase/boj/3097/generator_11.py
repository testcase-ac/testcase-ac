import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random
import math

# Constants for the problem
N_LOWER = 2  # Minimum number of segments
N_UPPER = 5  # Maximum number of segments
COORD_LOWER = -10  # Minimum value for X and Y coordinates
COORD_UPPER = 10  # Maximum value for X and Y coordinates

def generate_random_segment():
    """Generates a random segment (X, Y) within the defined bounds."""
    x = random.randint(COORD_LOWER, COORD_UPPER)
    y = random.randint(COORD_LOWER, COORD_UPPER)
    return (x, y)

def generate_testcase():
    """Generates a single test case."""
    N = random.randint(N_LOWER, N_UPPER)
    segments = [generate_random_segment() for _ in range(N)]
    
    print(f"{N}")
    for segment in segments:
        print(f"{segment[0]} {segment[1]}")
    
    return segments

def main():
    # Seed for reproducibility (optional)
    random.seed()
    
    # Generate random test cases based on random distribution
    generate_testcase()

if __name__ == "__main__":
    main()
