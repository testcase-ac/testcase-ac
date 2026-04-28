import sys
r = sys.stdin.readline

n = int(r())

def j_box(i):
	for _ in range(i): print("#", end="")
	print()
	for _ in range(i-2):
		print("#", end="")
		for _p in range(i-2): print("J", end="")
		print("#")
	if i > 1:
		for _ in range(i): print("#", end="")
		print()

for _ in range(n):
	j_box(int(r()))
	print()