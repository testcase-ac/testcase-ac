# Generates a large test to trigger TLE in the quadratic-time wrong solution
# n up to 100000, choose m ~ n/2 to maximize inner work
# Wages are all 1 (valid: 0 < T_i <= 1_000_000)

def main():
    n = 100000
    m = 50000
    print(n, m)
    # Print n ones, space-separated, no trailing space
    print("1 " * (n - 1) + "1")

if __name__ == "__main__":
    main()
