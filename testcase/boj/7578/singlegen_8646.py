import sys

def main():
    N = 100000
    # A: 1..N
    # B: N..1 (maximizes crossings -> exceeds 2^32-1 so the wrong solution overflows)
    w = sys.stdout.write
    w(str(N) + "\n")
    w(" ".join(map(str, range(1, N + 1))) + "\n")
    w(" ".join(map(str, range(N, 0, -1))) + "\n")

if __name__ == "__main__":
    main()
