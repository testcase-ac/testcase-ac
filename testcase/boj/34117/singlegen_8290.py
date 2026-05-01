# This generator creates a worst-case performance test for the wrong solution.
# The wrong solution maintains a sorted list via insertion with adjacent swaps,
# leading to O(N^2) behavior in adversarial cases. With strictly increasing A_i
# and large P, the maintained list stays large and every insertion bubbles to the
# front, causing TLE for N up to 500000.

import sys

def main():
    n = 500000
    p = 10**9
    print(n, p)
    w = sys.stdout.write
    for i in range(1, n + 1):
        if i > 1:
            w(' ')
        w(str(i))
    w('\n')

if __name__ == "__main__":
    main()
