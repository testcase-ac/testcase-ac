# Generates a worst-case input to cause TLE in the wrong O(N^2) solution
# Strategy: strictly decreasing prices so the algorithm advances only one edge per iteration
# N is set to the maximum (100000), distances are all 1.

def main():
    N = 100000
    print(N)
    # Distances: N-1 ones
    print(" ".join(["1"] * (N - 1)))
    # Prices: strictly decreasing from N to 1
    print(" ".join(str(N - i) for i in range(N)))

if __name__ == "__main__":
    main()
