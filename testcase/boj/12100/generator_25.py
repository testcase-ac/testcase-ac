import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for specifying bounds
N_MIN = 2   # Minimum grid size
N_MAX = 6   # Maximum grid size
VALUE_MIN_EXP = 1  # Minimum exponent for block value (2^VALUE_MIN_EXP)
VALUE_MAX_EXP = 10  # Maximum exponent for block value (2^VALUE_MAX_EXP)

def generate_random_case():
    """
    Generates a random test case with random blocks.
    Ensures at least one block is placed.
    """
    # Random N in range
    N = random.randint(N_MIN, N_MAX)
    # Generate random blocks
    board = []
    total_blocks = 0
    block_prob = random.random() * 0.7 + 0.3
    for _ in range(N):
        row = []
        for _ in range(N):
            # Decide whether to place a block or empty
            if random.random() < block_prob:
                # Place a block
                value_exp = random.randint(VALUE_MIN_EXP, VALUE_MAX_EXP)
                value = 2 ** value_exp
                total_blocks += 1
            else:
                # Empty cell
                value = 0
            row.append(value)
        board.append(row)
    # Ensure at least one block is placed
    if total_blocks == 0:
        x = random.randint(0, N-1)
        y = random.randint(0, N-1)
        value_exp = random.randint(VALUE_MIN_EXP, VALUE_MAX_EXP)
        value = 2 ** value_exp
        board[x][y] = value
    return N, board

def generate_single_block_case():
    """
    Generates a test case with a single block.
    """
    N = random.randint(N_MIN, N_MAX)
    board = [[0]*N for _ in range(N)]
    # Place a single block in a random position
    x = random.randint(0, N-1)
    y = random.randint(0, N-1)
    value_exp = random.randint(VALUE_MIN_EXP, VALUE_MAX_EXP)
    value = 2 ** value_exp
    board[x][y] = value
    return N, board

def generate_non_mergeable_blocks_case():
    """
    Generates a test case where no blocks can be merged.
    """
    N = random.randint(N_MIN, N_MAX)
    board = [[0]*N for _ in range(N)]
    exponents = list(range(VALUE_MIN_EXP, VALUE_MAX_EXP+1))
    random.shuffle(exponents)
    exp_index = 0
    for i in range(N):
        for j in range(N):
            # Assign different exponents to adjacent blocks
            exp = exponents[exp_index % len(exponents)]
            value = 2 ** exp
            board[i][j] = value
            exp_index += 1
    return N, board

def generate_large_merge_case():
    """
    Generates a test case designed to produce a large block after merges.
    """
    N = random.randint(N_MIN, N_MAX)
    board = [[0]*N for _ in range(N)]
    # Decide a number of layers to create
    layers = random.randint(2, N)
    for layer in range(layers):
        direction = random.choice(['row', 'column'])
        if direction == 'row':
            # Fill a row with 2's
            for j in range(N):
                board[layer][j] = 2
        else:
            # Fill a column with 2's
            for i in range(N):
                board[i][layer] = 2
    return N, board

def generate_test_case():
    """
    Randomly selects a test case type and generates it.
    """
    case_type = random.choice(['random', 'single_block', 'non_mergeable', 'large_merge'])
    if case_type == 'random':
        N, board = generate_random_case()
    elif case_type == 'single_block':
        N, board = generate_single_block_case()
    elif case_type == 'non_mergeable':
        N, board = generate_non_mergeable_blocks_case()
    elif case_type == 'large_merge':
        N, board = generate_large_merge_case()
    else:
        N, board = generate_random_case()
    return N, board

def main():
    N, board = generate_test_case()
    # Output the test case
    print(N)
    for row in board:
        print(' '.join(map(str, row)))

if __name__ == "__main__":
    main()
