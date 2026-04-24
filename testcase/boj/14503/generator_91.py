import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for room size
N_MIN = 3
N_MAX = 10
M_MIN = 3
M_MAX = 10

# Constants for wall probability
WALL_PROB_MIN = 0.1
WALL_PROB_MAX = 0.3

def generate_test_case():
    N = random.randint(N_MIN, N_MAX)
    M = random.randint(M_MIN, M_MAX)
    WALL_PROB = random.uniform(WALL_PROB_MIN, WALL_PROB_MAX)
    
    grid = [[0]*M for _ in range(N)]
    
    # Set outer borders to walls
    for i in range(N):
        grid[i][0] = 1
        grid[i][M-1] = 1
    for j in range(M):
        grid[0][j] = 1
        grid[N-1][j] = 1
    
    # Generate inner cells with walls or empty spaces
    for i in range(1, N-1):
        for j in range(1, M-1):
            if random.random() < WALL_PROB:
                grid[i][j] = 1  # Wall
            else:
                grid[i][j] = 0  # Empty space
    
    # Ensure there is at least one empty cell for the starting position
    empty_cells = [(i, j) for i in range(1, N-1) for j in range(1, M-1) if grid[i][j] == 0]
    if not empty_cells:
        # If no empty cells, make the center cell empty
        r, c = N // 2, M // 2
        grid[r][c] = 0
    else:
        # Randomly select a starting position from empty cells
        r, c = random.choice(empty_cells)
    
    # Random initial direction (0: North, 1: East, 2: South, 3: West)
    d = random.randint(0, 3)
    
    # Output the test case
    print(f"{N} {M}")
    print(f"{r} {c} {d}")
    for row in grid:
        print(' '.join(map(str, row)))

if __name__ == "__main__":
    generate_test_case()
