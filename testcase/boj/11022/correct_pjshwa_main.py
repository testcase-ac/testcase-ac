import sys
r = sys.stdin.readline

n = int(r())
for i in range(1, n+1):
	a, b = map(int, r().split())
	print("Case #{}: {} + {} = {}".format(i, a, b, a+b))