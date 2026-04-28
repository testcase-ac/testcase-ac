k, n = map(int, input().split())
if n == 1:
  print(-1)
else:
  x = n * k // (n - 1)
  while True:
    if x * (n - 1) >= k * n:
      print(x)
      break
    x += 1
