from collections import deque

n = int(input())

ls = list(map(int, input().split()))
a, b = map(int, input().split())
a -= 1
b -= 1
dist = [0 for _ in range(n)]
visited = [False for _ in range(n)]

q = deque([a])
visited[a] = True
while q:
    i = q.popleft()
    for j in range(i, n, ls[i]):
        if not visited[j]:
            visited[j] = True
            dist[j] = dist[i] + 1
            q.append(j)
    for j in range(i, -1, -ls[i]):
        if not visited[j]:
            visited[j] = True
            dist[j] = dist[i] + 1
            q.append(j)

if not visited[b]:
    print(-1)
else:
    print(dist[b])
