import sys

def main():
    # Construct a worst-case time input for the wrong solution:
    # 1,000,000 insertions followed by 1,000,000 deletions (type-2 queries),
    # forcing O(log^2 N) behavior repeatedly and likely causing TLE.
    N = 2_000_000
    w = sys.stdout.write
    w(str(N) + "\n")
    for _ in range(1_000_000):
        w("1 1\n")
    for _ in range(1_000_000):
        w("2 1\n")

if __name__ == "__main__":
    main()
