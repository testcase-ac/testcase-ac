t = int(input())
for _ in range(t):
  n = int(input())
  s = n * (n + 1) // 2

  l, r = 1, n
  while l < r:
    m = (l + r) // 2
    if m * (m + 1) <= s: l = m + 1
    else: r = m

  print(l)
