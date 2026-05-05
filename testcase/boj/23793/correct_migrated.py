import heapq
import sys
input = sys.stdin.readline

def dijkstra(graph, start,i,end):
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
            if i == 2 and n == y:
                continue
            if dist[n] > weight + w:
                dist[n] = weight + w
                heapq.heappush(sequence, (dist[n], n))

a,b = map(int, input().split())
graph = {i:[] for i in range(1, a + 1)}
for _ in range(b):
    a, b, c = map(int, input().split())
    graph[a].append((b, c))
x,y,z = map(int, input().split())
result1 = dijkstra(graph, x,1,y)
result2 = dijkstra(graph, y,1,z)
result3 = dijkstra(graph, x,2,z)
final_result = []
if result1 == None or result2 == None: final_result.append(-1)
else: final_result.append(result1 + result2)
if result3 == None: final_result.append(-1)
else: final_result.append(result3)
print(*final_result)
