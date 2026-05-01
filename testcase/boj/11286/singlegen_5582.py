# Generate a maximal test for the "absolute‐value heap" problem:
# N = 100000 operations: 50000 inserts, then 50000 pops.
print(100000)
# 50000 inserts: 1, -1, 2, -2, ..., 25000, -25000
for i in range(1, 25001):
    print(i)
    print(-i)
# 50000 pops
for _ in range(50000):
    print(0)
