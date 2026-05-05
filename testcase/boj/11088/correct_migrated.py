import sys
sys.setrecursionlimit(10000)
input = sys.stdin.readline

n = int(input().strip())
names = []
spoken = []
understands = []

for _ in range(n):
    parts = input().split()
    names.append(parts[0])
    spoken.append(parts[1])
    understands.append(set(parts[1:]))

adj = [[] for _ in range(n)]
for i in range(n):
    for j in range(n):
        if i != j and spoken[i] in understands[j]:
            adj[i].append(j)

index = 0
indices = [-1] * n
low = [0] * n
onstack = [False] * n
stack = []
scc_sizes = []

def dfs(v):
    global index
    indices[v] = index
    low[v] = index
    index += 1
    stack.append(v)
    onstack[v] = True
    for w in adj[v]:
        if indices[w] == -1:
            dfs(w)
            low[v] = low[v] if low[v] < low[w] else low[w]
        elif onstack[w]:
            if indices[w] < low[v]:
                low[v] = indices[w]
    if low[v] == indices[v]:
        cnt = 0
        while True:
            u = stack.pop()
            onstack[u] = False
            cnt += 1
            if u == v:
                break
        scc_sizes.append(cnt)

for v in range(n):
    if indices[v] == -1:
        dfs(v)
max_scc = max(scc_sizes) if scc_sizes else 0
print(n - max_scc)
