import heapq
import sys
input = sys.stdin.readline
t = int(input())

def dijkstra(graph, start):
    dist = [float('inf')] * (n + 1)
    dist[start] = 0
    sequence = [(0, start)]
    while sequence:
        weight, node = heapq.heappop(sequence)
        if dist[node] < weight:
            continue
        for n1,w in graph[node]:
            if dist[n1] > weight + w:
                dist[n1] = weight + w
                heapq.heappush(sequence, (weight+w, n1))
    return dist

for _ in range(t):
    n,m = map(int, input().split())
    graph = {i:[] for i in range(1, n + 1)}
    for _ in range(m):
        a, b, c = map(int, input().split())
        graph[a].append((b, c))
        graph[b].append((a, c))
    friend = int(input())
    friend_place = list(map(int, input().split()))
    result = []
    for i in friend_place:
        result.append(dijkstra(graph, i))
    final_result = [0] * (n+1)
    final_result[0] = float('inf')
    for i in range(1,n+1):
        for result_num in result:
            final_result[i] += result_num[i]
    print(final_result.index(min(final_result)))
