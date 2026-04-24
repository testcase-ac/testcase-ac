# Generates a long chain where the optimal distance exceeds 2,147,483,647 even after paving 1 road
# This exposes the bug where the wrong solution uses Integer.MAX_VALUE as INF for long distances.

def main():
    n = 2150  # cities
    m = n - 1 # roads in a chain
    k = 1     # can pave 1 road
    w = 1_000_000
    # Total path cost without paving: (n-1) * w = 2,149,000,000
    # Minimal with one pave: (n-2) * w = 2,148,000,000 (> 2,147,483,647)
    print(n, m, k)
    for i in range(1, n):
        print(i, i+1, w)

if __name__ == "__main__":
    main()
