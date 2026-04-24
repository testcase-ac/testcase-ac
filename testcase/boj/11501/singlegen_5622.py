# Generate a single test of maximum size N = 1_000_000
# Prices alternate between the minimum (1) and maximum (10_000),
# giving (N//2) profitable buy‐low/sell‐high pairs, each earning 9999.
N = 10**6
print(1)        # T = 1
print(N)        # N days
# Day prices: 1,10000,1,10000,...
# Profit per cycle = 10000 - 1 = 9999; cycles ≈ 500000 → total profit ≈ 5×10^9
for i in range(N):
    print(1 if i % 2 == 0 else 10000, end=' ')
