# Generates a path graph where di*ti exceeds 32-bit int, causing overflow in the wrong solution

def main():
    N = 46342  # minimal N so that (N-1) * N > 2^31-1
    M = N - 1
    R = 1
    print(f"{N} {M} {R}")
    for i in range(1, N):
        print(f"{i} {i+1}")

if __name__ == "__main__":
    main()
