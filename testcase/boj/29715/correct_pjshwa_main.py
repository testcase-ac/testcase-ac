import sys
r = sys.stdin.readline

n, m = map(int, r().split())
x, y = map(int, r().split())

def fac(n):
  ret = 1
  for i in range(1, n + 1): ret *= i
  return ret

def nCr(n, r):
  if n < 0 or r < 0 or n < r: return 0
  ret = fac(n)
  ret //= fac(r)
  ret //= fac(n - r)
  return ret

cand, fix = 9 - m, 0
for _ in range(m):
  a, b = map(int, r().split())
  if a == 0: fix += 1
  else: n -= 1

cnt = nCr(cand, n - fix) * fac(n)
xcnt, ycnt = cnt, (cnt - 1) // 3
print(x * xcnt + y * ycnt)
