
N = 1000
X = 500
edges = []
for i in range(1, N):
    edges.append((i,   i+1, 100))
    edges.append((i+1, i,   100))

print(N, len(edges), X)
for u, v, w in edges:
    print(u, v, w)
