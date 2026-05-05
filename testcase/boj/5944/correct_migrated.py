import heapq
import sys
input = sys.stdin.readline

def dijkstra(graph, start):
    dist = [float('inf')] * (len(graph) + 1)
    dist[start] = 0
    sequence = [(0, start)]
    while sequence:
        weight, node = heapq.heappop(sequence)
        if dist[node] < weight:
            continue
        for n, w in graph[node]:
            if dist[n] > weight + w:
                dist[n] = weight + w
                heapq.heappush(sequence, (dist[n], n))
    return dist
a,b,c,d,e = map(int, input().split())
graph = {i:[] for i in range(1, b + 1)}
for _ in range(a):
    f,g,h = map(int, input().split())
    graph[f].append((g,h))
    graph[g].append((f,h))
c_dist = dijkstra(graph,c)
d_dist = dijkstra(graph,d)
print(min(c_dist[d] + d_dist[e],c_dist[e] + d_dist[e]))
