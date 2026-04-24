# Generates a worst-case input for BOJ 14889 (Start and Link)
# The provided wrong solution explores permutations instead of combinations,
# leading to factorial blow-up. Using N=20 ensures TLE.

def main():
    n = 20
    print(n)
    for i in range(n):
        row = ['0' if i == j else '1' for j in range(n)]
        print(' '.join(row))

if __name__ == "__main__":
    main()
