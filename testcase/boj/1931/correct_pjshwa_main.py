import heapq, sys

n = int(input())
heap = []

for i in range(n):
	si, ti = map(int, sys.stdin.readline().split())
	heapq.heappush(heap, (ti, si))

meetings = 0
last_fi = 0
while heap:
	ti, si = heapq.heappop(heap)
	if si >= last_fi:
		last_fi = ti
		meetings += 1

print(meetings)
