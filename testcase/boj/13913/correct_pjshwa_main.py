import sys

n, k = map(int, sys.stdin.readline().split())
visit_list = [None] * 100001

def bfs(point):
	global k
	points_queue = [(point, 0, -1)]
	lim = lambda x: 0 <= x and x <= 100000
	def next_point_f(p):
		yield (2*p, 1)
		yield (p-1, 1)
		yield (p+1, 1)
	while(True):
		# print(points_queue)
		current_point, current_iteration, past_point = points_queue[0]
		del points_queue[0]
		if visit_list[current_point] is not None or not lim(current_point): continue
		visit_list[current_point] = past_point
		if current_point == k: break
		for next_point, step in next_point_f(current_point):
			if lim(next_point) and visit_list[next_point] is None:
				points_queue.append((next_point, current_iteration + step, current_point))
	return current_iteration

print(bfs(n))
history = []

while visit_list[k] != -1:
	history.append(k)
	k = visit_list[k]

history.append(n)
print(' '.join(map(str, reversed(history))))
