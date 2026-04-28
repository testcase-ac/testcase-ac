import sys
r = sys.stdin.readline

n = int(r())
if n == 1:
  print(1)
  exit()

if n % 2 == 1:
  print(-1)
  exit()

ans = [0] * (n + 1)
for i in range(2, n + 1, 2): ans[i] = i - 1
for i in range(1, n + 1, 2): ans[i] = n - i + 1
for i in range(1, n + 1): print(ans[i], end=' ')
print()
