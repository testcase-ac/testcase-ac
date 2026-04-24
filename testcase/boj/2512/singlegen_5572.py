# Generate a maximum testcase for the budget allocation problem:
# N at its upper bound, all requests at their upper bound,
# and total budget M slightly below the total sum to force binary-search capping.

N = 10_000
requests = [100_000] * N      # each request = 100,000 (max)
M = 900_000_000               # total budget < N * 100,000 = 1_000_000_000

print(N)
print(*requests)
print(M)
