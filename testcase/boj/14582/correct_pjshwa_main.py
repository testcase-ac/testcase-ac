import sys; r = sys.stdin.readline

geminis = map(int, r().split())
gullivers = map(int, r().split())

score_1, score_2 = 0, 0
overthrow = False

for i, j in zip(geminis, gullivers):
	score_1 += i
	if score_1 > score_2:
		overthrow = True
		break
  score_2 += j

if overthrow: print('Yes')
else: print('No')
