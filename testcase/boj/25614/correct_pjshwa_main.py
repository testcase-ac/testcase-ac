import sys
r = sys.stdin.readline

n, m = map(int, r().split())
a = list(map(lambda x: int(x) - 1, r().split()))
vis = [False] * n
ans = [-1] * n
mod = [-1] * (n + 1)

for i in range(n):
  if vis[i]: continue

  b = [i]
  while a[b[-1]] != i: b.append(a[b[-1]])

  if mod[len(b)] == -1: mod[len(b)] = m % len(b)
  for j, v in enumerate(b):
    vis[v] = True
    ans[v] = str(b[(j + mod[len(b)]) % len(b)] + 1)

print(' '.join(ans))
