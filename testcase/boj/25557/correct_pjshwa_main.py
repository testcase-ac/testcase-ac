import sys
from math import ceil, floor
rl = sys.stdin.readline

MAX = 2400
d = [[None] * (MAX + 1) for _ in range(MAX + 1)]
sys.setrecursionlimit(MAX + 50)

def r(k, y):
  if d[k][y] != None: return d[k][y]

  s, e = max(0, ceil(y / 2 - 1)), min(y, floor(y / 2 + 1))
  prob = 1 / (e - s + 1)
  ret = 0

  for i in range(s, e + 1):
    if i == k: ret += 1
    elif i > k: ret += r(k, i - 1) + 1
    else: ret += r(k - i - 1, y - i - 1) + 1

  d[k][y] = ret * prob
  return d[k][y]

t = int(rl())
for _ in range(t):
  x, y, k = map(int, rl().split())
  print(r(k - x, y - x))
