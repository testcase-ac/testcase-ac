# This generator creates a worst-case input that makes the given solution non-AC (TLE).
# Idea: Create one small cycle (1 <-> 2), and have every other node i (3..N) point to i-1.
# The wrong solution allocates an O(N)-sized vector for each start node and, crucially,
# when it hits an already-resolved node (grouped/never), it just breaks without marking
# the current path, causing long repeated traversals for many starts. This structure
# forces roughly O(N^2) work.

import sys

def main():
    T = 1
    N = 100000
    print(T)
    print(N)
    arr = [0]*(N+1)
    arr[1] = 2
    arr[2] = 1
    for i in range(3, N+1):
        arr[i] = i-1
    print(" ".join(map(str, arr[1:])))

if __name__ == "__main__":
    main()
