# Generate a maximum test case for the symmetric difference problem.
# N and M at their upper bounds (200,000 each), values all distinct
# to maximize symmetric-difference size (400,000).

N = 200000
M = 200000

# Print header
print(N, M)

# Print set A: 1, 2, ..., N
# Print set B: N+1, N+2, ..., N+M
# This ensures no overlap, so the symmetric difference size is N+M = 400,000
print(*range(1, N+1))
print(*range(N+1, N+M+1))
