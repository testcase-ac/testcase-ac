n = int(input())

current_danji = 1
danji_dict = {}
map_danji = []
visit_danji = [0] * (n**2)
for _ in range(n):
    for s in input().rstrip():
    	map_danji.append(s)

def bfs(point):
	global current_danji, danji_dict, map_danji, visit_danji
	q = [point]
	visit_danji[point] = current_danji
	apts = 0
	while(q):
		current_point = q[0]
		apts += 1
		if((current_point + 1) % n != 0 and map_danji[current_point+1] == '1' and visit_danji[current_point+1] == 0):
			visit_danji[current_point+1] = current_danji
			q.append(current_point+1)
		# left
		if((current_point % n) != 0 and map_danji[current_point-1] == '1' and visit_danji[current_point-1] == 0):
			visit_danji[current_point-1] = current_danji
			q.append(current_point-1)
		# up
		if(current_point >= n and map_danji[current_point-n] == '1' and visit_danji[current_point-n] == 0):
			visit_danji[current_point-n] = current_danji
			q.append(current_point-n)
		# down
		if(current_point < (n-1)*n and map_danji[current_point+n] == '1' and visit_danji[current_point+n] == 0):
			visit_danji[current_point+n] = current_danji
			q.append(current_point+n)
		del q[0]
		# print(apts, q)
	danji_dict[current_danji] = apts
	current_danji += 1

def print_farm(farm):
	for i, e in enumerate(farm):
		if (i % n == 0): print()
		print("{} ".format(e), end="")

for i in range(len(map_danji)):
	if map_danji[i] == '1' and visit_danji[i] == 0:
		bfs(i)
		# print_farm(visit_danji)

print(len(danji_dict))

for i in sorted(danji_dict.values()):
	print(i)
