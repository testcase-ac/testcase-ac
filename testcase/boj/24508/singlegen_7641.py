# Generates a large test that triggers integer overflow in the wrong Java solution's T (int) budget handling.
# The minimal number of moves required is 2,500,000,000 (> 2^31-1), but T=0.
# Due to 32-bit int overflow, the wrong solution will think T stayed non-negative and print YES, while the correct answer is NO.

def main():
    N = 100000
    K = 100000
    T = 0
    a = 50000
    print(f"{N} {K} {T}")
    print(" ".join([str(a)] * N))

if __name__ == "__main__":
    main()
