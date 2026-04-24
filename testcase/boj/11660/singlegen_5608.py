# Generates a maximal test for the 2D prefix‐sum problem:
# N = 1024 (max), M = 100000 (max), all cell values = 1000 (max),
# all queries spanning the full matrix (1,1)→(1024,1024).
N = 1024
M = 100000
print(N, M)
row = " ".join(["1000"] * N)
for _ in range(N):
    print(row)
for _ in range(M):
    print(1, 1, N, N)
