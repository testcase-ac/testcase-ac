import sys

n, m, k = map(int, sys.stdin.readline().split())
map_danji = [0] * (m*n)
danji_dict = {}
current_danji = 1
visit_danji = [0] * (m*n)
for i in range(k):
	p1, p2 = map(int, sys.stdin.readline().split())
	map_danji[(p1-1)*m + p2-1] = 1

def bfs(point):
	global current_danji, danji_dict, map_danji, visit_danji
	q = [point]
	visit_danji[point] = current_danji
	apts = 0
	while(q):
		current_point = q[0]
		apts += 1
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
	danji_dict[current_danji] = apts
	current_danji += 1

for i in range(len(map_danji)):
	if map_danji[i] == 1 and visit_danji[i] == 0:
		bfs(i)

print(max(danji_dict.values()))
