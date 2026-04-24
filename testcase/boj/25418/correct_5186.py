from collections import deque

a, k = map(int, input().split())

q = deque([a])
visited = [False] * (k+1)
dist = [0 for _ in range(k+1)]

while q:
    i = q.popleft()
    if i * 2 <= k and not visited[i * 2]:
        visited[i * 2] = True
        dist[i * 2] = dist[i] + 1
        q.append(i * 2)

    if i + 1 <= k and not visited[i + 1]:
        visited[i + 1] = True
        dist[i + 1] = dist[i] + 1
        q.append(i + 1)

print(dist[k])
