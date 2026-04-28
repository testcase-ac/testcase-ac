import sys; r = sys.stdin.readline
sys.setrecursionlimit(10**6)

n, R, q = map(int, r().split())
graph = [[] for _ in range(n + 1)]
vis = [False for _ in range(n + 1)]
size = [0 for _ in range(n + 1)] 
for _ in range(n - 1):
  u, v = map(int, r().split())
  graph[u].append(v)
  graph[v].append(u)

def countSubtreeNodes(currentNode):
  size[currentNode] = 1
  vis[currentNode] = True
  for node in graph[currentNode]:
    if vis[node]: continue
    countSubtreeNodes(node)
    size[currentNode] += size[node]

countSubtreeNodes(R)
for _ in range(q):
  u = int(r())
  print(size[u])
