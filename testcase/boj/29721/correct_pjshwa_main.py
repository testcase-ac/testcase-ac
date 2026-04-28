import sys
r = sys.stdin.readline

DX = [-2, 0, 2, 0]
DY = [0, 2, 0, -2]

n, k = map(int, r().split())
ori, mov = set(), set()
for _ in range(k):
  x, y = map(int, r().split())
  ori.add((x, y))

for x, y in ori:
  for l in range(4):
    nx, ny = x + DX[l], y + DY[l]
    if nx < 1 or nx > n or ny < 1 or ny > n: continue
    if (nx, ny) in ori: continue
    mov.add((nx, ny))

print(len(mov))
