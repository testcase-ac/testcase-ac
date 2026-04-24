import sys

def main():
    # Construct a max-sized test to force the O((N-K+1) * K log K) solution to TLE
    # N up to 250,000, K up to 5,000
    N = 250000
    K = 5000
    w = sys.stdout.write
    w(f"{N} {K}\n")

    # Generate pseudo-random-looking values in [0, 65535]
    # Use a simple xorshift32 to avoid any sorted/run-structured best cases
    x = 2463534242  # seed
    for _ in range(N):
        x ^= (x << 13) & 0xFFFFFFFF
        x ^= (x >> 17)
        x ^= (x << 5) & 0xFFFFFFFF
        w(f"{x & 0xFFFF}\n")

if __name__ == "__main__":
    main()
