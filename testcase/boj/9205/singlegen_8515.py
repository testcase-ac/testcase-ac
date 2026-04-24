# This generator creates a worst-case instance that forces the given DFS solution
# to explore essentially all permutations of stores (exponential time) and thus TLE.
# All 100 stores and the home are at the same coordinate, making the graph fully connected,
# while the festival is placed too far to reach from anywhere.

def main():
    n = 100
    print(1)
    print(n)
    print("0 0")  # home
    for _ in range(n):
        print("0 0")  # stores (all at home location)
    print("2000 0")  # festival (unreachable: distance 2000 > 1000)

if __name__ == "__main__":
    main()
