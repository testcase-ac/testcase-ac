# This generator creates a worst-case DAG for the wrong solution:
# - All build times are zero, so DP values remain 0 and memoization never triggers.
# - Fully connected DAG (i -> j for all i < j) makes the number of recursive calls
#   explode exponentially due to recomputation across exponentially many paths.
# This will cause TLE (non-AC) in the wrong solution.

def main():
    N = 35  # large enough to cause exponential blow-up
    K = N * (N - 1) // 2
    print(1)  # T
    print(N, K)
    print(' '.join(['0'] * N))  # all build times are 0
    for i in range(1, N):
        for j in range(i + 1, N + 1):
            print(i, j)
    print(N)  # target building W

if __name__ == "__main__":
    main()
