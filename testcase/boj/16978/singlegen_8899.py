# This generator creates a worst-case performance test for the wrong solution.
# It forces each type-2 query to iterate over all prior updates, leading to O(U*Q)
# behavior and causing TLE.

def main():
    n = 100000
    print(n)
    # Initial array: all ones
    print(' '.join(['1'] * n))

    m = 100000
    print(m)

    U = 50000  # number of updates
    # Perform U updates first (so all later queries see U updates to iterate over)
    # Update distinct positions from 1..U to value 2
    for i in range(1, U + 1):
        print(f"1 {i} 2")

    # Then perform Q = m - U queries, each asking for k=0 (no updates applied)
    # and over the full range [1, n], so every update is considered in the slow loop.
    for _ in range(m - U):
        print(f"2 0 1 {n}")

if __name__ == "__main__":
    main()
