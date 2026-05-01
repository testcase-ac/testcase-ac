# Generates a test that triggers out-of-bounds access in the wrong solution's indexer array
# The bug occurs when K >= 6 because indexer is indexed by position = 2^level - 1, which exceeds
# the size of the indexer array (size 16).

def main():
    K = 6
    N = (1 << K) - 1
    print(K)
    # Any permutation is valid as an inorder traversal; use 1..N for simplicity
    print(" ".join(str(i) for i in range(1, N + 1)))

if __name__ == "__main__":
    main()
