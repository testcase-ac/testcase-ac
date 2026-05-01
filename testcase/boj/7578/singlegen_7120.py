# Generator for BOJ 7578 (Factory) to break the wrong solution via 32-bit printf overflow
# Constructs a case where inversion count exceeds 2^31-1
# Smallest N such that N*(N-1)/2 > 2^31-1 is N=65537

def main():
    n = 65537
    # A: 1..n
    # B: n..1 (reverse), yielding maximum inversions = n*(n-1)//2 = 2,147,516,416
    A = range(1, n + 1)
    B = range(n, 0, -1)
    print(n)
    print(" ".join(map(str, A)))
    print(" ".join(map(str, B)))

if __name__ == "__main__":
    main()
