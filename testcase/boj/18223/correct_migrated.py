import heapq
import sys
input = sys.stdin.readline

def dijkstra(graph, start):
    distance = [float('inf')] * (len(graph) + 1)
    distance[start] = 0
    sequence = [(0, start)]
    while sequence:
        weight, node = heapq.heappop(sequence)
        if distance[node] < weight:
            continue
        for n,w in graph[node]:
            if distance[n] > weight + w:
                distance[n] = weight + w
                heapq.heappush(sequence, (distance[n], n))
    return distance
v,e,p = map(int, input().split())
graph = {i: [] for i in range(1, v + 1)}
for i in range(e):
    a, b, c = map(int, input().split())
    graph[a].append((b, c))
    graph[b].append((a, c))
path1 = dijkstra(graph, 1)
path2 = dijkstra(graph, p)
if path1[v] == path1[p] + path2[v]:
    print('SAVE HIM')
else:
    print('GOOD BYE')
