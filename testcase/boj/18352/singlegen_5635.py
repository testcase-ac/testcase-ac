# Generate a maximal test case for the problem
# N=300000 cities, M=299999 one‐way roads from city 1 to every other city,
# K=1 so that all 299999 other cities are at distance exactly 1 from X=1.

N = 300000
M = N - 1
K = 1
X = 1
print(N, M, K, X)
for v in range(2, N + 1):
    print(1, v)
