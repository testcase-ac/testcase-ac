# Generate a maximum test case for the range‐update & range‐sum problem
# N = 1e6 (max), M = 1e4 updates, K = 1e4 queries.
# Initial array all zeros.
# Do M full‐range +1 updates, then K full‐range sum queries.

N = 10**6
M = 10**4
K = 10**4

# 1) header
print(N, M, K)

# 2) initial array values
for _ in range(N):
    print(0)

# 3) M updates: add 1 to [1..N]
for _ in range(M):
    # a=1, b=1, c=N, d=1
    print(1, 1, N, 1)

# 4) K queries: sum over [1..N]
for _ in range(K):
    # a=2, b=1, c=N
    print(2, 1, N)
