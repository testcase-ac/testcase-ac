# Maximum testcase generator for the Olympic ranking problem
# N = 1000 (upper limit), K = 1000 (we query the country with the lowest gold count)
# Total medals = sum of golds = 1000+999+...+1 = 500500 <= 1_000_000
N, K = 1000, 1000
print(N, K)
for i in range(1, N+1):
    # Country i has gold = 1001 - i, silver = 0, bronze = 0
    print(i, 1001 - i, 0, 0)
