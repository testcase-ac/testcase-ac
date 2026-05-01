# Maximum testcase for the coin-change problem:
# n = 100 (max), k = 10000 (max)
# coin values = 1, 2, 3, …, 100
# This guarantees a solution (using 100×100-value coins) and forces the DP to
# fill the full table of size 100 × 10000.

n = 100
k = 10000
print(n, k)
for v in range(1, n+1):
    print(v)
