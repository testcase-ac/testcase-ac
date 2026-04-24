# Generate a single maximal test‐file:
# - T is very large to test input reading performance.
# - Every query uses the maximum allowed M, N, x, y = 40000.
#
# This stays within the problem constraints (1 ≤ M, N ≤ 40000; 1 ≤ x ≤ M; 1 ≤ y ≤ N).
# Solutions must handle up to 100000 cases of the worst sizes.

T = 100000
print(T)
for _ in range(T):
    print(40000, 40000, 40000, 40000)
