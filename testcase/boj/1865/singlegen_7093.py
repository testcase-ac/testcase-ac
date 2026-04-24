# Generates a single heavy case that satisfies all constraints:
# N=500, M=2500, W=1, weights in [1..10000].
# No negative cycle; your code runs Bellman–Ford from every node -> ~1.3B relax checks.

def main():
    F = 1
    N, M, W = 500, 2500, 1
    print(F)
    print(N, M, W)

    edges = []

    # 1) Heavy chain ensures large positive path costs and no negative cycle with the wormhole.
    for i in range(1, N):
        edges.append((i, i+1, 10000))  # 499 edges

    # 2) Fill up to exactly M edges with large positive weights.
    need = M - len(edges)  # 2001 more
    u, v = 1, 3
    while need > 0:
        if u == v:
            v = v % N + 1
        edges.append((u, v, 10000))
        u = (u * 37 + 11) % N + 1
        v = (v * 53 + 7) % N + 1
        need -= 1

    # Output M undirected edges
    for s, e, t in edges:
        print(s, e, t)

    # 3) One harmless wormhole (does not create a negative cycle)
    print(1, N, 1)

if __name__ == "__main__":
    main()
