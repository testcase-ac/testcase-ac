# Generates a worst-case input causing the provided O(N^2) bubble-sort simulation to time out
# Format: N on first line, then N lines with A[1..N]
# We choose N=500000 and a strictly decreasing sequence to maximize passes.
import sys

def main():
    N = 500000
    w = sys.stdout.write
    w(str(N) + "\n")
    for x in range(N, 0, -1):
        w(str(x) + "\n")

if __name__ == "__main__":
    main()
