n = int(input())

import sys
for i in range(n):
	var_it = map(int, sys.stdin.readline().split())
	_n = next(var_it)
	l = sorted(var_it)
	avg = sum(l) / _n
	no = _n
	for j in l:
		if j > avg: break
		no -= 1

	print("{0:00.3f}%".format(no * 100 / _n))