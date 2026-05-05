import heapq
import sys
input = sys.stdin.readline

def dijkstra(start):
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

a,b,c,d = map(int, input().split())
graph = {i:[] for i in range(1,a+1)}
for _ in range(b):
    e,f,g = map(int, input().split())
    graph[e].append((f, g))
    graph[f].append((e, g))
cow = [0] * (c + 1)
for i in range(1,c+1):
    cow[i] = int(input())
distance = dijkstra(1)
result = []
for i in range(1,c+1):
    if distance[cow[i]] <= d:
        result.append(i)
print(len(result))
result.sort()
for i in result:
    print(i)
