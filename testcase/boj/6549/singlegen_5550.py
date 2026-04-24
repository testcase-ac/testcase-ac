# Generates a single maximal test case (plus the terminating 0) for the largest-rectangle-in-a-histogram problem
n = 10**5
# Use the maximum allowed height 10^9 for every bar to maximize area = n * height = 10^14
print(n, *([10**9] * n))
print(0)
