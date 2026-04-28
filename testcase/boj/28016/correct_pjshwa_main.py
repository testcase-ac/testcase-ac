import sys
r = sys.stdin.readline

N, M = map(int, r().split())
B = [list(map(int, r().split())) for _ in range(N)]
d = [[0] * M for _ in range(N)]

# Init
for j in range(M):
  if B[0][j] == 2: d[0][j] = 1

for i in range(1, N):
  for j in range(M):
    if B[i][j] != 1: d[i][j] += d[i - 1][j] * 2
    else:
      if B[i][j - 1] != 1 and B[i - 1][j - 1] != 1: d[i][j - 1] += d[i - 1][j]
      if B[i][j + 1] != 1 and B[i - 1][j + 1] != 1: d[i][j + 1] += d[i - 1][j]

val, ans = 0, -1
for j in range(M):
  if d[N - 1][j] > val:
    val = d[N - 1][j]
    ans = j

print(ans)
