# long long overflow
# 300,000 * 300,000 * 1,000,000,000 > 2^64

N, M = 1, 300_000
print(N, M)
print(*[1]*M)
print(1_000_000_000)

Q = 300_000
print(Q)
for i in range(61489):
    print(1, M, 1_000_000_000)
print(1, M, 146_912_366)
for i in range(61490, Q):
    print(1, 1, 1)
