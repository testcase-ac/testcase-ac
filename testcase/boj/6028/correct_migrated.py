import heapq
import sys
input = sys.stdin.readline

def dijkstra(graph, start,end,i):
    global candy
    if len(graph) == 0:
        return -1
    dist = [float('inf')] * (len(graph) + 1)
    dist[start] = 0
    sequence = [(0, start)]
    while sequence:
        weight, node = heapq.heappop(sequence)
        if i == 2 and end == node:
            return dist[node]
        if dist[node] < weight:
            continue
        for n, w in graph[node]:
            if dist[n] > weight + w:
                dist[n] = weight + w
                heapq.heappush(sequence, (dist[n], n))
    return dist
a,b,c = map(int, input().split())
graph = {i:[] for i in range(1, a + 1)}
for _ in range(b):
    d,e,f = map(int, input().split())
    graph[d].append((e, f))
    graph[e].append((d, f))
one_distance = dijkstra(graph,1,1,1)
for _ in range(c):
    d,e = map(int, input().split())
    print(one_distance[d] + one_distance[e])
