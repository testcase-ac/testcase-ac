# Generate a maximum test case for N upN=1500
# Each column is strictly increasing downward,
# rows are in decreasing order just to avoid trivial sorted‐row patterns.
# The values range from 0 to N^2-1, all within [-1e9, 1e9].
N = 1500
print(N)
for i in range(N):
    # For row i, values run from i*N + (N-1) down to i*N
    row = [i * N + (N - 1 - j) for j in range(N)]
    print(" ".join(map(str, row)))
