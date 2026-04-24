# Generates a large test case that causes the O(N^2) wrong solution to TLE
# N = 100000, values are -1..-50000 and 1..50000 (all unique, valid)
# This ensures there exists a pair summing to 0, but the wrong solution
# still iterates over ~5e9 pairs and times out.

def main():
    import sys
    n = 100000
    print(n)
    nums = []
    # negatives: -1 to -50000
    for i in range(1, 50001):
        nums.append(str(-i))
    # positives: 1 to 50000
    for i in range(1, 50001):
        nums.append(str(i))
    sys.stdout.write(" ".join(nums))

if __name__ == "__main__":
    main()
