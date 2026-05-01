# Generate a worst‐case input for N=100000:
# The first gap is enormous, the rest are minimal (1), so gcd=1 and nearly 1e9 trees are needed.
N = 100000
print(N)
print(1)
# We need N-1 more positions, ending at 10^9, each incremented by 1
start = 10**9 - (N - 2)   # so that from start to 10^9 inclusive we get N-1 numbers
for x in range(start, 10**9 + 1):
    print(x)
