# Generate a worst‐case (maximum swaps) testcase for N up to 500,000:
# A is in strictly descending order, so the number of swaps = N*(N-1)/2.

N = 500000
print(N)
# print the sequence 500000, 499999, ..., 2, 1
print(*range(N, 0, -1))
