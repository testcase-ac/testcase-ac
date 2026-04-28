from collections import deque
import sys
r = sys.stdin.readline

n = int(r())
wline = [deque() for _ in range(n)]
total = 0

for i in range(n):
  wline[i].extend(map(int, r().split()))
  total += wline[i][0]
  wline[i].popleft()

invpos = [None] * (total + 1)
baspos = [0] * n
bassum = [0] * n

for i in range(n):
  for j, e in enumerate(wline[i]):
    invpos[e] = (i, j)
  for j in range(len(wline[i]) - 1):
    wline[i][j + 1] += wline[i][j]


def op1(x, y):
  gx, gy = invpos[x][0], invpos[y][0]
  if gx == gy:
    print('NO')
    return

  if len(wline[gx]) > len(wline[gy]):
    gx_sum = wline[gx][-1]
    last = bassum[gy]
    while wline[gy]:
      e = wline[gy].popleft()
      aval = e - last

      invpos[aval] = (gx, len(wline[gx]) - 1 + baspos[gx])
      wline[gx].append(gx_sum + e - last)

      last = e
    
  else:
    baspos[gy] -= len(wline[gx])
    bassum[gy] -= (wline[gx][-1] - bassum[gx])

    while wline[gx]:
      e = wline[gx].pop()
      aval = e - wline[gx][-1] if wline[gx] else e - bassum[gx]

      invpos[aval] = (gy, baspos[gy] + len(wline[gx]))
      wline[gy].appendleft(bassum[gy] + e - bassum[gx])

  print('YES')


def op2(x, y):
  if not invpos[x][0] == invpos[y][0]:
    print('-1')
    return

  g = invpos[x][0]
  posx = invpos[x][1] - baspos[g]
  posy = invpos[y][1] - baspos[g]
  if posx > posy: posx, posy = posy, posx

  if posx == 0: val = wline[g][posy] - bassum[g]
  else: val = wline[g][posy] - wline[g][posx - 1]
  print(val)


q = int(r())
# while True:
for _ in range(q):
  op, x, y = map(int, r().split())
  if op == 1: op1(x, y)
  if op == 2: op2(x, y)
