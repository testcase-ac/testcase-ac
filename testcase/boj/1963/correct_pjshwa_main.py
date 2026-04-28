import sys
r = sys.stdin.readline

primes_list = [True] * 10001
visited = [False] * 10001

primes_list[0] = False
primes_list[1] = False

n = int(r())


for i in range(0, 101):
	if primes_list[i]:
		idx = 2
		while i * idx <= 10000:
			primes_list[i * idx] = False
			idx += 1

def possible_nums(number):
	# over 1000
	# only one digit change
	# not visited

	def new_number(number_list_string):
		return int(''.join(number_list_string))

	whole_set = list(map(str, range(10)))
	list_string = list(str(number))
	for i in range(4):
		for item in whole_set:
			if item != list_string[i]:
				new = int("{}{}{}".format(''.join(list_string[:i]), item, ''.join(list_string[i+1:])))
				if new >= 1000 and not visited[new] and primes_list[new]: yield new

def bfs(number):
	global d, primes_list, visited
	q = []
	q.append((number, 0))
	visited[number] = True
	while q:
		cur, cur_idx = q[0]
		if cur == d: return cur_idx
		del q[0]
		for pn in possible_nums(cur):
			q.append((pn, cur_idx + 1))
			visited[pn] = True
	return None

for _ in range(n):

	s, d = map(int, r().split())
	result = bfs(s)
	if result is not None: print(result)
	else: print("Impossible")
	for i in range(10001): visited[i] = False

