import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for bounds
MIN_N = 1
MAX_N = 10  # Reduced to 10 for smaller test cases

MIN_H = 0
MAX_H = 10  # Heights are small for easy calculation

def generate_histogram():
    n = random.randint(MIN_N, MAX_N)
    if n == 1 and random.random() > 0.5:
        n = random.randint(MIN_N+1, MAX_N)
    heights = []

    # Randomly select a pattern to generate heights
    pattern = random.choice(['random',  'increasing', 'decreasing'])

    if pattern == 'random':
        heights = [random.randint(MIN_H, MAX_H) for _ in range(n)]
    elif pattern == 'increasing':
        heights = sorted([random.randint(MIN_H, MAX_H) for _ in range(n)])
    elif pattern == 'decreasing':
        heights = sorted([random.randint(MIN_H, MAX_H) for _ in range(n)], reverse=True)

    return f"{n} {' '.join(map(str, heights))}"

# Generate two test cases and print them followed by a 0
def generate_multiple_histograms():
    count = random.randint(1, 2)
    for _ in range(count):
        print(generate_histogram())
    print(0)  # Print the terminating zero

# Generate and print the test cases
generate_multiple_histograms()
