import heapq, sys
r = sys.stdin.readline
h = []

n = int(r())
for _ in range(n):
	op = r().rstrip()
	# print(h)
	if op == '0':
		if h: print(heapq.heappop(h))
		else: print(op)
	else:
		heapq.heappush(h, int(op))
