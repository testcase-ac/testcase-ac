t = int(input())
MOD = int(1e9 + 7)
for _ in range(t):
  c = int(input())
  n = ans = 1
  for _ in range(c):
    pi, ai = map(int, input().split())
    it = pow(pi, ai, MOD)
    sg = it * ai + (pow(pi, ai + 1, MOD) + (MOD - 1)) * pow(pi - 1, MOD - 2, MOD)
    n = (n * it) % MOD
    ans = (ans * sg) % MOD
  print((n + ans) % MOD)
