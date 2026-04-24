# Generates a worst-case test for the given wrong solution (BOJ 9466 variant)
# This creates a long chain of length n-1 leading into a self-loop at n.
# The provided solution uses deep recursion per start and lacks memoization,
# causing recursion depth ~ n and overall O(n^2) work, likely leading to RTE/TLE.

import sys

def main():
    n = 100000
    print(1)
    print(n)
    # 1->2, 2->3, ..., n-1->n, n->n
    arr = list(range(2, n+1)) + [n]
    print(' '.join(map(str, arr)))

if __name__ == "__main__":
    main()
