t = int(input())
for _ in range(t):
  n = bin(int(input()))
  sz = len(n)
  pw = 1
  ans = 0
  for i in range(sz - 1, 1, -1):
    if n[i] == '1': ans += pw
    pw *= 3
  print(ans)
