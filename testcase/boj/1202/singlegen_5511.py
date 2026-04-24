# Generates a maximum testcase for the jewellery‐thief problem with N=K=300000
N = 300_000
K = 300_000

print(N, K)
# N items: each of mass 1 and value 1_000_000
for _ in range(N):
    print(1, 1_000_000)
# K bags: each with capacity 1 (so every item fits)
for _ in range(K):
    print(1)
