import heapq, sys, math

n = int(input())
heap = []

for i in range(n):
  xi, wi = map(int, sys.stdin.readline().split())
  heapq.heappush(heap, (xi + wi, xi - wi))

meetings = 0
last_fi = -math.inf
while heap:
  ti, si = heapq.heappop(heap)
  if si >= last_fi:
    last_fi = ti
    meetings += 1

print(meetings)
