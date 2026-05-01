# This generator produces a large test where the Java solution overflows its 32-bit int sum
# N = 100000, K = 100000, T = 99999
# A_i = 99999 for all i, so sum = 99,999 * 100,000 = 9,999,900,000 > 2^31-1
# Correct answer: YES (sum % K == 0 and minimal moves = 99,999 <= T)
# Wrong solution will overflow sum and incorrectly conclude sum % K != 0, printing NO.

def main():
    N = 100000
    K = 100000
    T = 99999
    print(f"{N} {K} {T}")
    print(" ".join(["99999"] * N))

if __name__ == "__main__":
    main()
