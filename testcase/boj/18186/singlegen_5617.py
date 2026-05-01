# Generate a maximum test case for the ramen‐buying problem
# N = 10^6 (maximum number of factories)
# B, C = 10^6 (maximum costs)
# Ai = 10^6 for all i (maximum demand per factory)

import sys

N = 10**6
B = 10**6
C = 10**6

# Print first line: N, B, C
sys.stdout.write(f"{N} {B} {C}\n")

# Print second line: A1 … AN (all = 10^6)
# We stream out the numbers to avoid building a huge string in memory.
for i in range(N):
    sys.stdout.write("1000000" + (" " if i < N-1 else ""))
