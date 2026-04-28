n = int(input())
a = list(map(int, input().split()))
o = list(map(int, input().split()))
r = []

def dfs(i, s):
  if i == n:
    r.append(s)
    return
  else:
    if o[0]:
      o[0] -= 1
      dfs(i + 1, s + a[i])
      o[0] += 1
    if o[1]:
      o[1] -= 1
      dfs(i + 1, s - a[i])
      o[1] += 1
    if o[2]:
      o[2] -= 1
      dfs(i + 1, s * a[i])
      o[2] += 1
    if o[3]:
      o[3] -= 1
      dfs(i + 1, int(s / a[i]))
      o[3] += 1

dfs(1, a[0])
print(max(r))
print(min(r))
