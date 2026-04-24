# Generates a maximum-size test for the problem
# N = 10^6, M = 10^4 updates, K = 10^4 queries

N = 10**6
M = 10**4
K = 10**4

# Print the header
print(N, M, K)

# 1) The initial array of length N, each value ≤ 1_000_000
for _ in range(N):
    print(1_000_000)

# 2) M updates: set position 1 to 0 (repeatedly)
#    (a = 1, b = 1, c = 0)
for _ in range(M):
    print(1, 1, 0)

# 3) K full-range product queries: query [1..N]
#    (a = 2, b = 1, c = N)
for _ in range(K):
    print(2, 1, N)
