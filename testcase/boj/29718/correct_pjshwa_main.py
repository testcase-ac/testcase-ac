import sys
r = sys.stdin.readline

n, m = map(int, r().split())
board = [list(map(int, r().split())) for _ in range(n)]

a = int(r())
cur = 0
for j in range(a):
  for i in range(n): cur += board[i][j]

ans = cur
for j in range(a, m):
  for i in range(n): cur += board[i][j] - board[i][j - a]
  ans = max(ans, cur)

print(ans)
