t = int(input())

import sys
for _ in range(t):
	n = int(input())
	votes_list = []
	for i in range(n):
		votes_list.append(int(input()))
	x, y = sorted(votes_list)[-2:]
	if x == y: print("no winner")
	else:
		v = sum(votes_list)
		if y / v > 0.5: print("majority winner {}".format(votes_list.index(y) + 1))
		else: print("minority winner {}".format(votes_list.index(y) + 1))