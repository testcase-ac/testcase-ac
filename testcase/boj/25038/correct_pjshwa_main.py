MOD = 202112210950

def matmul(a, b):
  n = len(a)
  c = [[0] * n for _ in range(n)]
  for i in range(n):
    for j in range(n):
      for k in range(n):
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD
  return c

def biinfinite(t, n):
  if n >= 0 and n < t:
    return 5701 if n & 1 else 5702
  elif n >= t:
    ans = [[0] * t for _ in range(t)]
    a = [[0] * t for _ in range(t)]
    for i in range(t): ans[i][i] = 1
    for i in range(t - 1): a[i][i + 1] = 1
    for i in range(t): a[t - 1][i] = i + 1

    k = n - t + 1
    while k:
      if k & 1: ans = matmul(ans, a)
      a = matmul(a, a)
      k >>= 1
    
    res = 0
    for i in range(t): res = (res + ans[t - 1][i] * biinfinite(t, i)) % MOD
    return res
  else:
    ans = [[0] * t for _ in range(t)]
    a = [[0] * t for _ in range(t)]
    for i in range(t): ans[i][i] = 1
    for i in range(t - 1): a[i][i + 1] = 1
    a[t - 1][0] = 1
    for i in range(t - 1): a[t - 1][i + 1] = -t + i

    k = -n
    while k:
      if k & 1: ans = matmul(ans, a)
      a = matmul(a, a)
      k >>= 1

    res = 0
    for i in range(t): res = (res + ans[t - 1][i] * biinfinite(t, t - i - 1)) % MOD
    return res

