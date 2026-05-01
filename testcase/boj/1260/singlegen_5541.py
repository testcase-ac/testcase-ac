# Generate a maximal test case for DFS/BFS problem
# N = 1000 nodes, M = 10000 edges, start at V = 1
N = 1000
M = 10000
V = 1
print(N, M, V)

# 1) Add a simple chain to ensure connectivity: 1-2-3-...-1000 (999 edges)
for i in range(1, N):
    print(i, i + 1)

# 2) Add the remaining edges (10000 - 999 = 9001 edges) using a simple deterministic pattern
#    This will introduce many extra connections (and some duplicates) to stress sorting and duplicate handling.
extra = M - (N - 1)
for i in range(extra):
    u = (i % N) + 1
    v = ((i * 7 + 3) % N) + 1
    print(u, v)
