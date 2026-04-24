# Generate a maximum test case for the Kevin-Bacon problem:
# N = 100 (maximum users), M = 4950 (all possible undirected edges among 100 nodes)
N = 100
M = N * (N - 1) // 2
print(N, M)
for i in range(1, N + 1):
    for j in range(i + 1, N + 1):
        print(i, j)
