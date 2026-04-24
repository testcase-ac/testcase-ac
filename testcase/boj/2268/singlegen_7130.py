# This generator creates a case that triggers 32-bit integer overflow in the wrong solution.
# It sets many elements to 100000 such that the total sum exceeds 2^31-1.
# N = 21475, M = N + 1. We set A[1..N] = 100000, then query sum(1, N).

def main():
    n = 21475
    m = n + 1
    print(n, m)
    for i in range(1, n + 1):
        print(1, i, 100000)
    print(0, 1, n)

if __name__ == "__main__":
    main()
