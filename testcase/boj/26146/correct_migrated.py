import sys
input = sys.stdin.readline

n, m = map(int, input().split())
adj = [[] for _ in range(n + 1)]
radj = [[] for _ in range(n + 1)]
for _ in range(m):
    v, w = map(int, input().split())
    adj[v].append(w)
    radj[w].append(v)
visited = [False] * (n + 1)
order = []

for i in range(1, n + 1):
    if not visited[i]:
        stack = [(i, 0)]
        visited[i] = True
        while stack:
            v, idx = stack[-1]
            if idx < len(adj[v]):
                stack[-1] = (v, idx + 1)
                u = adj[v][idx]
                if not visited[u]:
                    visited[u] = True
                    stack.append((u, 0))
            else:
                stack.pop()
                order.append(v)
visited2 = [False] * (n + 1)
scc_count = 0
for v in reversed(order):
    if not visited2[v]:
        scc_count += 1
        if scc_count > 1:
            print("No")
            sys.exit(0)
        stack = [v]
        visited2[v] = True
        while stack:
            x = stack.pop()
            for y in radj[x]:
                if not visited2[y]:
                    visited2[y] = True
                    stack.append(y)
print("Yes")
