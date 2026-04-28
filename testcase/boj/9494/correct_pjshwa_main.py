import sys
r=sys.stdin.readline

n = int(r())
while n != 0:
	lines = []
	for _ in range(n):
		lines.append("{} ".format(r().rstrip()))
	col = 0
	for i in range(n):
		try:
			space_i = lines[i][col:].index(' ')
			col += space_i
		except ValueError:
			continue
	print(col + 1)
	n = int(r())