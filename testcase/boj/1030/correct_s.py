s, n, k, r1, r2, c1, c2 = map(int, input().split())

def fractal(i, j):
  for scale in range(s, 0, -1):
    ns = n ** scale; i, j = i % ns, j % ns
    r = range(*map(lambda x: x * ns // 2 // n, (n - k, n + k)))
    if i in r and j in r: return 1
  return 0

for i in range(r1, r2 + 1):
  print(*[fractal(i, j) for j in range(c1, c2 + 1)], sep='')