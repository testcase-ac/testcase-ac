# Generate maximum test case for "New Recruits"
# T = 1, N = 100000 (max), and pairs (i, N+1-i) for i=1..N
# This sequence ensures all N applicants will be selected,
# and it hits the largest input size.

N = 10**5
print(1)
print(N)
for i in range(1, N+1):
    print(i, N+1 - i)
