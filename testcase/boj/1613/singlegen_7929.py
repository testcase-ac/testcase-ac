# Generates a worst-case input for BOJ 1613 (History)
# This stresses the wrong solution by forcing it to run two full BFS traversals
# per query without early exit, across a dense DAG. This should lead to TLE.

import sys

def main():
    n = 400
    M = 150  # each node points to next up to 150 nodes, creating a dense DAG

    edges = []
    for i in range(1, n + 1):
        for d in range(1, M + 1):
            j = i + d
            if j <= n:
                edges.append((i, j))

    k = len(edges)  # should be 48675

    out_lines = []
    out_lines.append(f"{n} {k}\n")
    for a, b in edges:
        out_lines.append(f"{a} {b}\n")

    s = 50000
    out_lines.append(f"{s}\n")

    # Query chosen so both BFS(a,b) and BFS(b,a) traverse large portions of the graph.
    # From 200, you can reach many later nodes; from 1, you can reach almost all nodes.
    query = "200 1\n"
    out_lines.extend([query] * s)

    sys.stdout.write(''.join(out_lines))

if __name__ == "__main__":
    main()
