import sys
r = sys.stdin.readline

n = int(r())
theses = sorted(map(int, r().split()))

q_index = n
while q_index != 0:
	if theses[n-q_index] < q_index:
		q_index -= 1
	else:
		break
print(q_index)