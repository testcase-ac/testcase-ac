# This generator creates a worst-case input for the given wrong solution.
# Grid is constructed so moves from bottom-right can go only up or left (strictly increasing heights),
# creating an exponential number of paths, but the target cell (0,0) is made too small to be entered,
# so every reachable node has 0 paths to the base. Because the wrong code treats dp=0 as "unvisited",
# it recomputes subproblems exponentially and will TLE.

def main():
    M = 500
    N = 500
    print(f"{M} {N}")
    for i in range(M):
        row = []
        for j in range(N):
            if i == 0 and j == 0:
                val = 1  # Make the destination minimal so it cannot be entered from neighbors
            else:
                # Monotone increasing when moving up/left: higher neighbors are up or left only
                val = 10000 - (i + j)
            row.append(str(val))
        print(" ".join(row))

if __name__ == "__main__":
    main()
