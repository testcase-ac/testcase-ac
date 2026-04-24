# Generate a maximal test for N=5000
# We include:
#  - 2498 very large negative numbers starting from -1e9
#  - three “middle” numbers whose sum is exactly zero (-2, -1, 3)
#  - 2499 very large positive numbers ending just below +1e9
N = 5000
print(N)
# 2498 negatives: -1000000000, -999999999, ..., -1000000000+2497
neg = [-10**9 + i for i in range(2498)]
# three numbers summing to zero
mid = [-2, -1, 3]
# 2499 positives: 1000000000-2499, 1000000000-2498, ..., 1000000000-1
pos = [10**9 - 2499 + i for i in range(2499)]
# concatenate and print
arr = neg + mid + pos
print(" ".join(map(str, arr)))
