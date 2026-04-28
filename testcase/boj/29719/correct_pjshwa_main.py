import sys
r = sys.stdin.readline

MOD = 10 ** 9 + 7

n, m = map(int, r().split())
ans = (pow(m, n, MOD) - pow(m - 1, n, MOD) + MOD) % MOD
print(ans)
