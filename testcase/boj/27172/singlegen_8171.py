# Generates a large test to cause O(N^2) wrong solution to TLE
# Valid per problem: N up to 100000, values 1..1_000_000, all distinct

def main():
    n = 100000
    print(n)
    print(' '.join(str(i) for i in range(1, n + 1)))

if __name__ == "__main__":
    main()
