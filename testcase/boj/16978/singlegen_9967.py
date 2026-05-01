# This generator creates a case where the segment tree overflows 32-bit int sums.
# N=3000 with all elements = 1,000,000 makes total sum = 3,000,000,000 (> 2^31-1),
# causing the wrong solution (which stores tree values in int) to produce an incorrect result.

def main():
    n = 3000
    print(n)
    print(" ".join(["1000000"] * n))
    print(1)
    print(f"2 0 1 {n}")

if __name__ == "__main__":
    main()
