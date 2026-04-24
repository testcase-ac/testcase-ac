import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for upper and lower bounds
N_MIN = 1       # Minimum number of floors
N_MAX = 10      # Maximum number of floors
M_MIN = 1       # Minimum number of participants
M_MAX = 10      # Maximum number of participants
H_MIN = 1       # Minimum hand height
H_MAX = 10000   # Maximum hand height

def generate_testcase():
    """
    Generates a single valid input for the problem.
    The type of testcase is selected randomly to ensure variety.
    Occasionally includes maximum height.
    """
    # Randomly select a testcase type
    testcase_type = random.randint(1, 4)
    
    # Decide whether to include maximum height
    include_max_height = random.choice([True, False, False])  # 1/3 chance to include maximum height
    
    if testcase_type == 1:
        # Type 1: Random N and M, random unique heights
        N = random.randint(N_MIN, N_MAX)
        M = random.randint(M_MIN, M_MAX)
        total_hands = 2 * M
        used_heights = set()
        heights = []
        if include_max_height:
            # Include H_MAX in possible heights
            possible_heights = set(range(H_MIN, H_MAX + 1))
            used_heights.add(H_MAX)
            heights.append(H_MAX)
            while len(heights) < total_hands:
                h = random.randint(H_MIN, H_MAX - 1)
                if h not in used_heights:
                    used_heights.add(h)
                    heights.append(h)
        else:
            while len(heights) < total_hands:
                h = random.randint(H_MIN, H_MAX)
                if h not in used_heights:
                    used_heights.add(h)
                    heights.append(h)
        random.shuffle(heights)
        hands = []
        for i in range(M):
            h1 = heights[2 * i]
            h2 = heights[2 * i + 1]
            hands.append((h1, h2))

    elif testcase_type == 2:
        # Type 2: Heights in increasing order
        N = random.randint(N_MIN, N_MAX)
        M = random.randint(M_MIN, N_MAX)
        total_hands = 2 * M
        if include_max_height and total_hands <= (H_MAX - H_MIN + 1):
            # Make sure we can include H_MAX
            start_height = H_MAX - total_hands + 1
            heights = list(range(start_height, H_MAX + 1))
        else:
            heights = list(range(H_MIN, H_MIN + total_hands))
        hands = []
        for i in range(M):
            h1 = heights[2 * i]
            h2 = heights[2 * i + 1]
            hands.append((h1, h2))

    elif testcase_type == 3:
        # Type 3: Heights in decreasing order
        N = random.randint(N_MIN, N_MAX)
        M = random.randint(M_MIN, N_MAX)
        total_hands = 2 * M
        if include_max_height and total_hands <= (H_MAX - H_MIN + 1):
            # Include H_MAX
            heights = list(range(H_MAX - total_hands + 1, H_MAX + 1))
            heights.reverse()
        else:
            heights = list(range(H_MIN + total_hands - 1, H_MIN - 1, -1))
        hands = []
        for i in range(M):
            h1 = heights[2 * i]
            h2 = heights[2 * i + 1]
            hands.append((h1, h2))

    elif testcase_type == 4:
        # Type 4: Heights including maximum height
        N = random.randint(N_MIN, N_MAX)
        M = random.randint(M_MIN, M_MAX)
        total_hands = 2 * M
        # Ensure unique heights including H_MAX
        if total_hands <= (H_MAX - H_MIN + 1):
            heights = random.sample(range(H_MIN, H_MAX + 1), total_hands)
            if include_max_height and H_MAX not in heights:
                heights[-1] = H_MAX  # Replace last element with H_MAX
            random.shuffle(heights)
        else:
            heights = list(range(H_MIN, H_MIN + total_hands))
        hands = []
        for i in range(M):
            h1 = heights[2 * i]
            h2 = heights[2 * i + 1]
            hands.append((h1, h2))
    else:
        # Default case: Random unique heights
        N = random.randint(N_MIN, N_MAX)
        M = random.randint(M_MIN, M_MAX)
        total_hands = 2 * M
        used_heights = set()
        heights = []
        while len(heights) < total_hands:
            h = random.randint(H_MIN, H_MAX)
            if h not in used_heights:
                used_heights.add(h)
                heights.append(h)
        hands = []
        for i in range(M):
            h1 = heights[2 * i]
            h2 = heights[2 * i + 1]
            hands.append((h1, h2))

    # Output the generated testcase
    print(f"{N} {M}")
    for h1, h2 in hands:
        print(f"{h1} {h2}")

# Generate the testcase
generate_testcase()
