xb = [0] * 100001
yb = [0] * 100001

import sys
r = sys.stdin.readline

n, m = map(int, r().split())
for i in range(n):
  x, y = map(int, r().split())
  xb[x] ^= 1
  yb[y] ^= 1
for i in range(m):
  x, y = map(int, r().split())
  xb[x] ^= 1
  yb[y] ^= 1

if sum(xb) + sum(yb) == 0: print('YES')
else: print('NO')
