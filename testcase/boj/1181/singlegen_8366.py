# Max-stress TLE test: N=20000 identical max-length words (50 chars)
# The wrong solution uses O(N^2) bubble sorts and compares 50 chars each time,
# leading to an enormous number of character comparisons ( ~10^10 ), likely TLE.

N = 20000
print(N)
w = "z" * 50
for _ in range(N):
    print(w)
