# Generate a maximum testcase for the “숫자 카드” problem
# N = 500 000 unique cards, M = 500 000 queries
# First half of queries all present, second half all absent.

N = 500_000
M = 500_000

# Print N and the N card values (1 through 500000)
print(N)
print(*range(1, N+1))

# Print M and then M queries:
#   1 to 250000  (all present)
#   500001 to 750000 (all absent, within ±10^7)
print(M)
# first M//2 queries: exactly the first half of the cards (will output 1)
for x in range(1, M//2 + 1):
    print(x, end=' ')
# next M//2 queries: values not in the set (will output 0)
for x in range(N+1, N+1 + M//2):
    print(x, end=' ')
