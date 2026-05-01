# Generate a maximum-size test for coordinate compression:
# N = 1e6, and all X_i are distinct to maximize the number of ranks.
N = 10**6
print(N)
step = 2000
# This will produce values from -1e9, -1e9+2000, -1e9+4000, ..., staying within [-1e9, 1e9].
# All values are distinct, so the compressed coordinates run from 0 to N-1.
out = []
x = -10**9
for _ in range(N):
    out.append(str(x))
    x += step
print(" ".join(out))
