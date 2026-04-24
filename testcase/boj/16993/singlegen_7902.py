# Generates a worst-case input to force TLE in the wrong solution
# Idea: The wrong solution recomputes Kadane for every query in O(length) time.
# With N=100000 and M=100000 and all queries covering the whole array, it will do ~1e10 iterations.
# We ensure its special-cased [lelele, ririri] pair does not match our queries by making the global
# maximum subarray start at index 2, while our queries are [1, N].

n = 100000
arr = [-1] + [1] * (n - 1)  # max subarray is [2..n]
m = 100000

print(n)
print(' '.join(map(str, arr)))
print(m)
for _ in range(m):
    print(f"1 {n}")
