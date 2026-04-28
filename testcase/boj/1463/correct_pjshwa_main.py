import sys

n = int(input())

def bfs(point):
	visit_list = [False] * 1000001
	points_queue = [(point, 0)]
	def next_point_f(p):
		if p % 3 == 0:
			yield p//3
		if p % 2 == 0:
			yield p//2
		yield p-1
	while(True):
		# print(points_queue)
		current_point, current_iteration = points_queue[0]
		del points_queue[0]
		if current_point == 1: break
		if visit_list[current_point]: continue
		visit_list[current_point] = True
		for next_point in next_point_f(current_point):
			if not visit_list[next_point]: points_queue.append((next_point, current_iteration + 1))
	return current_iteration

print(bfs(n))
