# Generate a max-size test:
# N = number of jewels, K = number of bags (both up to 300_000)
# We set jewel weights 1..N and values N..1 (so values and weights both ≤ 1_000_000)
# All bag capacities = 100_000_000 (so any bag can carry any jewel).
# This forces the solution to pick the top-K valued jewels out of N.

N = K = 300_000
print(N, K)
# Jewels: weight i, value N+1-i
for i in range(1, N+1):
    print(i, N+1-i)
# Bags: capacity large enough to hold any jewel
for _ in range(K):
    print(100000000)
