# Generate a heavy test to expose the performance issue (TLE) in the wrong Java solution.
# Construct N=10000, M=100000 with a dense backward "10-previous" linkage so that
# from many starting nodes the DFS visits almost all nodes and scans almost all edges,
# making the per-start work ~O(M) and total ~O(N*M).
# Edge format: A B meaning A trusts B.

def main():
    n = 10000
    edges = []
    # For each j, add trust from the previous up-to-10 nodes to j
    for j in range(2, n + 1):
        limit = min(10, j - 1)
        for k in range(1, limit + 1):
            edges.append((j - k, j))  # (A, B): A trusts B
    # Currently we have 99945 edges. Add 55 more unique edges of the form (j-11, j)
    added = 0
    j = 12
    while len(edges) < 100000 and j <= n:
        edges.append((j - 11, j))
        j += 1
    # Output
    print(f"{n} {len(edges)}")
    for a, b in edges:
        print(a, b)

if __name__ == "__main__":
    main()
