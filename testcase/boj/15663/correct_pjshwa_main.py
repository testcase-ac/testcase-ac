def dfs(current, visited):
  if len(current)==m: ans.add(current)
  else:
    for i in range(n):
      if i in visited: continue
      visited.append(i)
      dfs(current + (data[i],), visited)
      visited.pop()

n,m=map(int,input().split())
data=tuple(map(int,input().split()))
ans=set()
for i in range(n): dfs((data[i], ), [i])

for i in sorted(ans):
  for j in i: print(j, end=' ')
  print()
