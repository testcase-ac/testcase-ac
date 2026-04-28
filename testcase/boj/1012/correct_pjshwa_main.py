nn = int(input())

import sys
for _ in range(nn):
	m, n, k = map(int, sys.stdin.readline().split())
	map_danji = [0] * (m*n)
	current_danji = 1
	visit_danji = [0] * (m*n)
	for i in range(k):
		p1, p2 = map(int, sys.stdin.readline().split())
		map_danji[p1 + p2*m] = 1

	def bfs(point):
		global current_danji, map_danji, visit_danji
		q = [point]
		visit_danji[point] = current_danji
		apts = 0
		while(q):
			current_point = q[0]
			if((current_point + 1) % m != 0 and map_danji[current_point+1] == 1 and visit_danji[current_point+1] == 0):
				visit_danji[current_point+1] = current_danji
				q.append(current_point+1)
			# left
			if((current_point % m) != 0 and map_danji[current_point-1] == 1 and visit_danji[current_point-1] == 0):
				visit_danji[current_point-1] = current_danji
				q.append(current_point-1)
			# up
			if(current_point >= m and map_danji[current_point-m] == 1 and visit_danji[current_point-m] == 0):
				visit_danji[current_point-m] = current_danji
				q.append(current_point-m)
			# down
			if(current_point < (n-1)*m and map_danji[current_point+m] == 1 and visit_danji[current_point+m] == 0):
				visit_danji[current_point+m] = current_danji
				q.append(current_point+m)
			del q[0]
		current_danji += 1

	for i in range(len(map_danji)):
		if map_danji[i] == 1 and visit_danji[i] == 0:
			bfs(i)
	print(current_danji-1)
