# This generator creates a worst-case instance for the brute-force TSP solution.
# It outputs a fully connected graph with N=16 and unit weights (except zero diagonals).
# The wrong solution explores all permutations (and even restarts from every city),
# which will time out.

def main():
    n = 16
    print(n)
    for i in range(n):
        row = ['0' if i == j else '1' for j in range(n)]
        print(' '.join(row))

if __name__ == "__main__":
    main()
