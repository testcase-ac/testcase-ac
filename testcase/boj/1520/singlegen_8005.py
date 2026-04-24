# Generates a 17x17 grid where height strictly decreases when moving right or down.
# Number of downhill paths equals C(32,16) = 601,080,390 (<= 1e9),
# which the wrong DFS (without memoization) will try to enumerate, leading to TLE.

def main():
    M = 17
    N = 17
    print(f"{M} {N}")
    for i in range(M):
        row = []
        for j in range(N):
            # Strictly decreasing to the right and downward
            val = (M - 1 - i) + (N - 1 - j) + 1  # top-left is M+N-1, bottom-right is 1
            row.append(str(val))
        print(" ".join(row))

if __name__ == "__main__":
    main()
