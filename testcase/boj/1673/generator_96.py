import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

def generate_testcases():
    # Constants defining the bounds of n and k
    MIN_N = 2
    MAX_N = 100  # Keeping n small for easy verification
    MIN_K = 2

    num_testcases = random.randint(2, 5)  # Number of test cases to generate
    testcases = []

    for _ in range(num_testcases):
        while True:
            # Randomly select a case type to generate edge cases
            case_type = random.randint(1, 5)

            if case_type == 1:
                # Case 1: n = k
                n = random.randint(MIN_N, MAX_N)
                k = n
            elif case_type == 2:
                # Case 2: n = k + 1
                k = random.randint(MIN_K, MAX_N - 1)
                n = k + 1
            elif case_type == 3:
                # Case 3: n is a multiple of k
                k = random.randint(MIN_K, MAX_N // 2)
                m = random.randint(2, MAX_N // k)
                n = k * m
                if n > MAX_N:
                    continue
            elif case_type == 4:
                # Case 4: n just one less than a multiple of k
                k = random.randint(MIN_K, MAX_N // 2)
                m = random.randint(2, (MAX_N + 1) // k)
                n = k * m - 1
                if n < MIN_N or n > MAX_N:
                    continue
            else:
                # Case 5: Random n and k within bounds
                n = random.randint(MIN_N, MAX_N)
                k = random.randint(MIN_K, n)

            # Ensure that n and k satisfy the problem constraints
            if MIN_N <= n <= MAX_N and MIN_K <= k <= n:
                testcases.append(f"{n} {k}")
                break

    # Print the test cases, each on a new line
    for testcase in testcases:
        print(testcase)

# Generate and print the test cases
generate_testcases()
