import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for bounds (can be modified as needed)
MIN_N = 2    # Minimum number of people
MAX_N = 10   # Maximum number of people

def generate_testcase():
    # Randomly select the number of people N
    N = random.randint(MIN_N, MAX_N)
    
    # Types of distribution
    testcase_type = random.choice(["sparse", "dense", "mixed"])

    # Initialize friendship matrix
    friendships = [['N' for _ in range(N)] for _ in range(N)]

    if testcase_type == "sparse":
        # Sparse: Few friendships
        for i in range(N):
            for j in range(i + 1, N):
                if random.random() < 0.1:  # 10% chance of being friends
                    friendships[i][j] = 'Y'
                    friendships[j][i] = 'Y'

    elif testcase_type == "dense":
        # Dense: Many friendships
        for i in range(N):
            for j in range(i + 1, N):
                if random.random() < 0.9:  # 90% chance of being friends
                    friendships[i][j] = 'Y'
                    friendships[j][i] = 'Y'

    elif testcase_type == "mixed":
        # Mixed: Random mix of friendships
        for i in range(N):
            for j in range(i + 1, N):
                if random.random() < 0.5:  # 50% chance of being friends
                    friendships[i][j] = 'Y'
                    friendships[j][i] = 'Y'

    # Print the test case in the required format
    print(N)
    for row in friendships:
        print(''.join(row))

# Generate a test case
generate_testcase()
