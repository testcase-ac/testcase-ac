import sys; r = sys.stdin.readline

sys.setrecursionlimit(10 ** 6)

t = int(r())

# to find SCCs in digraphs:
# 1. do a whole dfs in G reverse
# 2. find the source SCC in G reverse (which in fact becomes sink in G)
# 3. delete them and repeat until no vertex left (label them in this case)

for i in range(t):
	n, m = map(int, r().split())
	conn_dict = {i:[] for i in range(1, n+1)}
	for j in range(m):
		x, y = map(int, r().split())
		conn_dict[x].append(y)

	visited = [0] * (n+1)
	visited_clock = [False] * (n+1)
	cc = 0
	
	time_list = [[-1,-1] for i in range(n+1)]
	clock = 0
	finish_time_dict = {}
	def clock_dfs(v):
		global clock
		visited_clock[v] = True
		clock += 1
		time_list[v][0] = clock
		for conn_vertex in conn_dict[v]:
			if visited_clock[conn_vertex] == False: clock_dfs(conn_vertex)
		clock += 1
		time_list[v][1] = clock
		finish_time_dict[clock] = v

	for vertex in range(1, n+1):
		if visited_clock[vertex] == False: clock_dfs(vertex)

	finish_time_order = [v[1] for v in sorted(finish_time_dict.items(), key = lambda x: -x[0])]

	def dfs(v, cc):
		visited[v] = cc
		for conn_vertex in conn_dict[v]:
			if visited[conn_vertex] == 0: dfs(conn_vertex, cc)

	for vertex in finish_time_order:
		if visited[vertex] == 0:
			cc += 1
			dfs(vertex, cc)


	print(cc)


