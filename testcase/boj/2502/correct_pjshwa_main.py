import sys
r = sys.stdin.readline

d, k = map(int, r().split())
a = 0
b = 1
c = 1
for _ in range(d-2):
	c = a + b
	a, b = b, c

# a, b is now coefs
def solve(c1, c2, target):
	x = 1
	y = 1
	while(c1*x + c2*y != target):
		y += 1
		if c1*x + c2*y > target:
			x += 1
			y = 1
	return (x, y)

print("{}\n{}".format(*solve(a, b, k)))