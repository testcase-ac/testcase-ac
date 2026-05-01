# Generate a maximal test case for the BFS problem:
# N = 100000 nodes, M = 200000 edges, R = 1 as start.
#
# We build:
# 1) A simple chain 1–2, 2–3, …, 99999–100000   (99999 edges)
# 2) 50000 “long” edges (u, u+50000) for u=1..50000
# 3) 25000 “mid” edges (u, u+25000) for u=1..25000
# 4) 25000 “upper-mid” edges (u, u+75000) for u=1..25000
# 5) One extra edge (1,100000)
#
# Total edges = 99999 + (50000+25000+25000) + 1 = 200000

N = 100_000
M = 200_000
R = 1
print(N, M, R)

# 1) Chain edges
for u in range(1, N):
    print(u, u+1)

# 2) Offset 50000
for u in range(1, 50000+1):
    print(u, u+50000)

# 3) Offset 25000
for u in range(1, 25000+1):
    print(u, u+25000)

# 4) Offset 75000
for u in range(1, 25000+1):
    print(u, u+75000)

# 5) Extra edge
print(1, N)
