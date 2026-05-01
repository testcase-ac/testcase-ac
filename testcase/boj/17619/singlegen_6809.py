# Generate a maximum-sized test for the "frog‐jumps‐on‐logs" problem.
# N = 100 000 logs, Q = 100 000 queries.
# Each log spans the full x‐range [0, 10^9] at distinct y = 1..N,
# so the frog can jump between any two adjacent logs vertically.
# Queries ask connectivity between log i and i+1 for all i and one extra (1, N).

N = 100000
Q = 100000
print(N, Q)
# Logs: x1=0, x2=1e9, y = 1..N
for y in range(1, N+1):
    print(0, 10**9, y)
# Queries: (1,2), (2,3), ..., (N-1, N), plus (1, N)
for i in range(1, N):
    print(i, i+1)
print(1, N)
