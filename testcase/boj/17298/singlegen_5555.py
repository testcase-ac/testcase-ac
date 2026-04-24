# Generate a maximum-size test for the Next Greater Element problem
# N = 1,000,000, A_i ∈ [1,1e6], strictly decreasing so every NGE = -1
N = 10**6
print(N)
# Print the sequence 1_000_000, 999_999, ..., 1
# This is simple, maximal N, and worst-case for naive approaches
print(' '.join(str(i) for i in range(N, 0, -1)))
