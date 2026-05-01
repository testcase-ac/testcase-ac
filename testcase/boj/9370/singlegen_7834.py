# Grid-based stress test to trigger TLE in the wrong solution due to enqueuing all equal-length paths
# Constructs a 20x100 grid (2000 nodes) with unit weights, start at top-left (1),
# special edge g-h as (1,2), and destination candidate at bottom-right (2000).
# This grid has an enormous number of equal-length shortest paths, causing the
# wrong solution to enqueue exponentially many equal-cost states (it relaxes on equality),
# leading to non-AC (TLE/MLE).

def main():
    R, C = 20, 100  # R*C = 2000 nodes
    n = R * C
    # number of undirected edges in grid
    m = R * (C - 1) + (R - 1) * C
    t = 1
    s = 1
    g, h = 1, 2  # edge (1,2) exists in the grid

    def id_of(r, c):
        return (r - 1) * C + c

    out_lines = []
    out_lines.append("1")  # T
    out_lines.append(f"{n} {m} {t}")
    out_lines.append(f"{s} {g} {h}")

    # horizontal edges
    for r in range(1, R + 1):
        for c in range(1, C):
            a = id_of(r, c)
            b = id_of(r, c + 1)
            out_lines.append(f"{a} {b} 1")

    # vertical edges
    for r in range(1, R):
        for c in range(1, C + 1):
            a = id_of(r, c)
            b = id_of(r + 1, c)
            out_lines.append(f"{a} {b} 1")

    # candidates: bottom-right corner
    out_lines.append(str(n))

    print("\n".join(out_lines))

if __name__ == "__main__":
    main()
