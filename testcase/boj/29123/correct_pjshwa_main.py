import sys, math
sys.setrecursionlimit(10 ** 6)

a, b = map(int, input().split())
g = math.gcd(a, b)

# 3d
dp = [[[-1 for _ in range(31)] for _ in range(31)] for _ in range(31)]

def rec(x, y, c, dp):
  if dp[x][y][c] != -1: return dp[x][y][c]
  if x == 0 and y == 0 and c == 0: return False

  ret = False

  # divide from x
  for i in range(1, x + 1):
    # i: subtract amount
    # j: subtract amount exclusive to x
    for j in range(min(i, x - c) + 1):
      if c - i + j < 0: continue
      ret = ret or not rec(x - i, y, c - i + j, dp)

  # divide from y
  for i in range(1, y + 1):
    # i: subtract amount
    # j: subtract amount exclusive to y
    for j in range(min(i, y - c) + 1):
      if c - i + j < 0: continue
      ret = ret or not rec(x, y - i, c - i + j, dp)

  # divide from both
  for i in range(1, c + 1):
    ret = ret or not rec(x - i, y - i, c - i, dp)

  print('x = {}, y = {}, c = {}, ret = {}'.format(x, y, c, ret))
  dp[x][y][c] = ret
  return ret

xc, yc, cc = 0, 0, 0

for i in range(2, int(a ** 0.5) + 1):
  while a % i == 0: a //= i; xc += 1
if a > 1: xc += 1

for i in range(2, int(b ** 0.5) + 1):
  while b % i == 0: b //= i; yc += 1
if b > 1: yc += 1

for i in range(2, int(g ** 0.5) + 1):
  while g % i == 0: g //= i; cc += 1
if g > 1: cc += 1

print('xc, yc, cc', xc, yc, cc)

if rec(xc, yc, cc, dp): print("Lucky wins")
else: print("Alf wins")
