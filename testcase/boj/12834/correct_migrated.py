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

a,b,c = map(int, input().split())
graph = {i:[] for i in range(1, b + 1)}
kist,seed_egg = map(int, input().split())
home = [0] + list(map(int, input().split()))
for _ in range(c):
    d,e,f = map(int, input().split())
    graph[e].append((d, f))
    graph[d].append((e, f))
result = 0
for i in home:
    if i == 0:
        continue
    temp = dijkstra(graph, i)
    if temp[kist] == float('inf'): result -= 1
    else: result += temp[kist]
    if temp[seed_egg] == float('inf'): result -= 1
    else: result += temp[seed_egg]
print(result)
