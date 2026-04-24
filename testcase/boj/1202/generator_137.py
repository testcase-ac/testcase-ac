import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for upper and lower bounds
MAX_N_K = 5           # Upper bound for N and K
MAX_M_V = 10          # Upper bound for Mi and Vi
MAX_C = 15            # Upper bound for Ci

MIN_M_V = 0           # Lower bound for Mi and Vi
MIN_C = 1             # Lower bound for Ci

def generate_test_case():
    N = random.randint(1, MAX_N_K)
    K = random.randint(1, MAX_N_K)

    print(f"{N} {K}")

    jewels = []
    for _ in range(N):
        Mi = random.randint(MIN_M_V, MAX_M_V)
        Vi = random.randint(MIN_M_V, MAX_M_V)
        jewels.append((Mi, Vi))
        print(f"{Mi} {Vi}")

    bags = []
    for _ in range(K):
        Ci = random.randint(MIN_C, MAX_C)
        bags.append(Ci)
        print(f"{Ci}")

if __name__ == "__main__":
    generate_test_case()
