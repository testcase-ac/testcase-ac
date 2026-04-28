import sys

n, k = map(int, sys.stdin.readline().split())

def bfs(point):
	global k
	visit_list = [False] * 100001
	points_queue = [(point, 0)]
	lim = lambda x: 0 <= x and x <= 100000
	def next_point_f(p):
		yield 2*p
		yield p+1
		yield p-1
	while(True):
		# print(points_queue)
		current_point, current_iteration = points_queue[0]
		del points_queue[0]
		if current_point == k: break
		if visit_list[current_point] or not lim(current_point): continue
		visit_list[current_point] = True
		for next_point in next_point_f(current_point):
			if lim(next_point) and not visit_list[next_point]: points_queue.append((next_point, current_iteration + 1))
	return current_iteration

print(bfs(n))