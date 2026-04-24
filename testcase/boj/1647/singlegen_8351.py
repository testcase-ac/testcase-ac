import sys

def main():
    # Construct a worst-case input for the given Prim-like implementation to cause TLE/MLE.
    # Use minimal N=2 to keep formatting simple, and maximal M=1_000_000.
    # One cheap edge to ensure connectivity, and the rest are parallel expensive edges.
    # This forces the algorithm to push ~1,000,000 edges from node 1 into the heap,
    # and store 2,000,000 adjacency entries, which is prohibitively heavy in PyPy.
    N = 2
    M = 1_000_000
    out = sys.stdout
    out.write(f"{N} {M}\n")
    # Base connecting edge
    out.write("1 2 1\n")
    # Add M-1 parallel edges with maximum allowed weight
    line = "1 2 1000\n"
    for _ in range(M - 1):
        out.write(line)

if __name__ == "__main__":
    main()
