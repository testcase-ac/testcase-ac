import heapq
import sys
input = sys.stdin.readline
def dijkstra(graph,start):
    dist = [float('inf')] * (len(graph) + 1)
    dist[start] = 0
    sequence = [(0, start)]
    while sequence:
        weight, node = heapq.heappop(sequence)
        if dist[node] < weight:
            continue
        for n,w in graph[node]:
            if dist[n] > weight + w:
                dist[n] = weight + w
                heapq.heappush(sequence, (weight + w, n))
    return dist
a = int(input())
graph = {i:[] for i in range(1, a+1)}
friend1, friend2,friend3 = map(int, input().split())
b = int(input())
for _ in range(b):
    d,e,l = map(int, input().split())
    graph[e].append((d, l))
    graph[d].append((e, l))

dij_fr1 = dijkstra(graph,friend1)
dij_fr2 = dijkstra(graph,friend2)
dij_fr3 = dijkstra(graph,friend3)
result = [0] * (a+1)
for i in range(1, a+1):
    result[i] = min(dij_fr1[i], dij_fr2[i], dij_fr3[i])
print(result.index(max(result)))
