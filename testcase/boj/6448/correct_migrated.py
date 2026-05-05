import heapq
import sys
input = sys.stdin.readline

def dijkstra(graph, start):
    global candy
    if len(graph) == 0:
        return -1
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
    dist[0] = 0
    return dist
while True:
    a = int(input())
    if a == 0:
        break
    graph = {i: [] for i in range(1, a + 1)}
    for k in range(1,a+1):
        b = list(map(int, input().split()))
        if len(b) == 1:
            continue
        i,j = 1,2
        for _ in range(b[0]):
            graph[k].append((b[i], b[j]))
            i += 2
            j += 2
    result = []
    for i in range(1, a + 1):
        result.append(max(dijkstra(graph, i)))
    print(result.index(min(result)) + 1, min(result))
