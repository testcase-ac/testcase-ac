import heapq
import sys
input = sys.stdin.readline

def dijkstra(graph, start,end):
    if len(graph) == 0:
        return -1
    dist = [float('inf')] * (len(graph) + 1)
    dist[start] = 0
    sequence = [(0, start)]
    while sequence:
        weight, node = heapq.heappop(sequence)
        if node == end:
            return dist[node]
        if dist[node] < weight:
            continue
        for n, w in graph[node]:
            if dist[n] > weight + w:
                dist[n] = weight + w
                heapq.heappush(sequence, (dist[n], n))
    return -1
a,b = map(int, input().split())
graph = {i:[] for i in range(1, a + 1)}
for _ in range(b):
    permission = list(map(int, input().split()))
    if permission[0] == 1:
        graph[permission[1]].append((permission[2], permission[3]))
        graph[permission[2]].append((permission[1], permission[3]))
    else:
        print(dijkstra(graph, permission[1], permission[2]))
