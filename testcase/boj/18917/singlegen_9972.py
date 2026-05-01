# Generates a worst-case test for the wrong solution causing TLE due to O(M^2) removals.
# Strategy:
# - Insert N distinct values 1..N
# - Remove them in reverse order N..1 (each removal scans from start to near end)
# - Add a single type-3 query to satisfy output requirement

N = 249_999
M = 2 * N + 1
print(M)
for i in range(1, N + 1):
    print(f"1 {i}")
for i in range(N, 0, -1):
    print(f"2 {i}")
print("3")
