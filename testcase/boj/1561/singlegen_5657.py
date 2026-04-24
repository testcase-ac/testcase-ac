# Generates a maximal test for the amusement‐park queue problem:
# N = 2e9 (maximum), M = 1e4 (maximum), ride times cycle through 1…30
N = 2_000_000_000
M = 10_000
print(N, M)
# produce M times in a simple repeating pattern 1,2,…,30,1,2,…,30,...
times = [(i % 30) + 1 for i in range(M)]
print(" ".join(map(str, times)))
