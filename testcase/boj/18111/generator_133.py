import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for upper and lower bounds
MAX_N = 5  # Maximum number of rows
MIN_N = 1  # Minimum number of rows
MAX_M = 5  # Maximum number of columns
MIN_M = 1  # Minimum number of columns
MAX_HEIGHT = 256  # Maximum block height
MIN_HEIGHT = 0  # Minimum block height
MAX_B = 20  # Maximum initial blocks in inventory
MIN_B = 0   # Minimum initial blocks in inventory

# Randomly choose N and M within bounds
N = random.randint(MIN_N, MAX_N)
M = random.randint(MIN_M, MAX_M)

# Randomly choose B within bounds
B = random.randint(MIN_B, MAX_B)

# Generate the grid of heights
grid = []

# Decide randomly the type of grid to generate
grid_type = random.choice(['random', 'flat', 'one_high', 'alternating', 'multiple_optimal'])

if grid_type == 'random':
    # Completely random heights
    for _ in range(N):
        row = [random.randint(MIN_HEIGHT, MAX_HEIGHT) for _ in range(M)]
        grid.append(row)
elif grid_type == 'flat':
    # All cells have the same height
    height = random.randint(MIN_HEIGHT, MAX_HEIGHT)
    for _ in range(N):
        row = [height] * M
        grid.append(row)
elif grid_type == 'one_high':
    # All cells have height MIN_HEIGHT except one cell with MAX_HEIGHT
    for _ in range(N):
        row = [MIN_HEIGHT] * M
        grid.append(row)
    i = random.randint(0, N-1)
    j = random.randint(0, M-1)
    grid[i][j] = MAX_HEIGHT
elif grid_type == 'alternating':
    # Cells with alternating heights
    for i in range(N):
        row = []
        for j in range(M):
            if (i + j) % 2 == 0:
                row.append(MIN_HEIGHT)
            else:
                row.append(MAX_HEIGHT)
        grid.append(row)
elif grid_type == 'multiple_optimal':
    # Create a grid where multiple heights have the same minimal time
    # For simplicity, we can create a grid with two heights
    h1 = random.randint(MIN_HEIGHT, MAX_HEIGHT - 1)
    h2 = h1 + 1
    for _ in range(N):
        row = [random.choice([h1, h2]) for _ in range(M)]
        grid.append(row)
else:
    # Default to random
    for _ in range(N):
        row = [random.randint(MIN_HEIGHT, MAX_HEIGHT) for _ in range(M)]
        grid.append(row)

# Output the test case
print(f"{N} {M} {B}")
for row in grid:
    print(' '.join(map(str, row)))
