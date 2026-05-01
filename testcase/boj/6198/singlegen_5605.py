# Maximum test case for N=80,000 with a strictly decreasing sequence of heights
# This triggers the worst‐case of the O(N) stack/monotonic solution
N = 80000
print(N)
for h in range(N, 0, -1):
    print(h)
