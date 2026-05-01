# Generate maximum testcase for the palindrome‐query problem
# N at its upper bound, M at its upper bound, trivial sequence so every query is palindrome
N = 2000
M = 10**6

print(N)
# Sequence of N identical numbers (all 1s)
print(" ".join(["1"] * N))
print(M)
# Repeat the widest-possible query (1, N) M times
for _ in range(M):
    print(1, N)
