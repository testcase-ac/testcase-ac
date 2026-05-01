# This generator creates a worst-case input for the O(n^2) solution:
# N is maximal and all elements are zero with K=0, forcing ~2e10 checks (TLE).
# Additionally, if it were to finish, the count would overflow 32-bit int.

import sys

n = 200000
k = 0
sys.stdout.write(f"{n} {k}\n")
sys.stdout.write(("0 " * (n - 1)) + "0\n")
