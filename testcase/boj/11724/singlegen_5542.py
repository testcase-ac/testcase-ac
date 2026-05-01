# Generate a maximum-size test for N=1000 with all possible edges (complete graph)
N = 1000
M = N * (N - 1) // 2
print(N, M)
for u in range(1, N):
    for v in range(u + 1, N + 1):
        print(u, v)
