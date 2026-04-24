import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants
N_MIN = 5
N_MAX = 20
K_MIN = 0
K_MAX = 25
L_MIN = 1
L_MAX = 25
X_MAX = 50
APPLE_ON_PATH_PROBABILITY = 0.7

# Directions: (dy, dx) for Right (R), Down (D), Left (L), Up (U)
DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # [R, D, L, U]

def generate_test_case():
    # Step 1: Choose a random board size N
    N = random.randint(N_MIN, N_MAX)
    
    # Step 2: Generate a snake's path (initially starts from (1, 1))
    snake_path = [(1, 1)]  # (row, col) starting at top-left corner
    current_direction = 0  # Start by moving to the right (R)
    
    # Generate a reasonable path of the snake (without collisions)
    for _ in range(2 * N):  # Generate enough steps in the path
        last_y, last_x = snake_path[-1]
        dy, dx = DIRECTIONS[current_direction]
        next_y, next_x = last_y + dy, last_x + dx
        
        # Ensure the next move is within bounds
        if 1 <= next_y <= N and 1 <= next_x <= N:
            snake_path.append((next_y, next_x))
        else:
            # If we hit a wall, change direction (randomly turn left or right)
            current_direction = (current_direction + random.choice([-1, 1])) % 4

    # Step 3: Precompute all available positions to place apples
    all_positions = {(i, j) for i in range(1, N + 1) for j in range(1, N + 1)}
    available_positions = all_positions - set(snake_path)  # Avoid placing apples on the initial snake's path
    
    # Ensure (1,1) is not an apple position
    available_positions.discard((1, 1))

    K = random.randint(K_MIN, min(K_MAX, N * N - 1))  # Number of apples to place
    apple_positions = set()

    # Place apples efficiently by picking random positions
    while len(apple_positions) < K:
        if random.random() < APPLE_ON_PATH_PROBABILITY and len(snake_path) > 1:
            # Place apple on the snake's path
            apple_position = random.choice(snake_path)
        else:
            # Place apple randomly in available positions
            if available_positions:
                apple_position = random.choice(list(available_positions))
                available_positions.remove(apple_position)
            else:
                break

        # Ensure no apple is placed at (1, 1)
        if apple_position != (1, 1) and apple_position not in apple_positions:
            apple_positions.add(apple_position)
    K = len(apple_positions)
    # Step 4: Generate direction changes L
    L = random.randint(L_MIN, L_MAX)
    direction_changes = []
    time = 0
    for _ in range(L):
        time += random.randint(1, min(5, X_MAX // L))  # Keep time increments small to fit within the X_MAX limit
        turn = random.choice(['L', 'D'])
        direction_changes.append((time, turn))

    # Step 5: Output the generated test case
    print(N)  # Board size
    print(K)  # Number of apples
    for apple in apple_positions:
        print(apple[0], apple[1])  # Apple positions
    print(L)  # Number of direction changes
    for change in direction_changes:
        print(change[0], change[1])  # Direction change time and type

# Running the test case generator
generate_test_case()
