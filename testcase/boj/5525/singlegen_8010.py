# This generator creates a worst-case input to cause TLE for the wrong solution.
# It sets N = 250000, M = 1000000, and S as an alternating string "IO" repeated 500000 times.
# The wrong solution performs an O(M * N) check over many starting indices, leading to TLE.

import sys

def main():
    n = 250000
    m = 1000000
    s = "IO" * (m // 2)  # length exactly 1_000_000
    print(n)
    print(m)
    print(s)

if __name__ == "__main__":
    main()
