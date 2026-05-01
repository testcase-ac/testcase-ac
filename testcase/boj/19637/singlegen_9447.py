import sys

def main():
    N = 100000
    M = 100000
    w = sys.stdout.write
    w(f"{N} {M}\n")
    # Titles with strictly increasing upper bounds to force worst-case linear scan per query
    for i in range(1, N + 1):
        w(f"A {i}\n")
    # All queries equal to the largest upper bound so the loop scans all N titles each time
    for _ in range(M):
        w(f"{N}\n")

if __name__ == "__main__":
    main()
