N = 500
M = 6000

# Start with printing N and M
print(N, M)

# Add chain edges to ensure that every iteration updates one new node.
# This creates 499 edges from 1->2, 2->3, ..., 499->500.
for i in range(1, N):
  print(i, i+1, 1)

# Add remaining dummy edges.
# These edges do not update any distances (1 -> 1 with 0 cost) but are processed every time.
dummy_edges = M - (N - 1)
for _ in range(dummy_edges):
  print(1, 1, 0)
