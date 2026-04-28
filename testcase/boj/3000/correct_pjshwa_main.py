import sys, itertools

n = int(input())
points = []

for i in range(n):
	points.append(list(map(int, sys.stdin.readline().split())))

triangles = itertools.combinations(points, 3)

def is_triangle(t):
	l = t
	if (l[0][0] == l[1][0] and l[0][1] == l[2][1]) or (l[2][1] == l[0][1] and l[2][0] == l[1][0]) or (l[1][1] == l[0][1] and l[1][0] == l[2][0]) or (l[1][0] == l[0][0] and l[1][1] == l[2][1]):
		return True
	else:
		return False

num_of_triangles = 0
for t in triangles:
	if is_triangle(t): num_of_triangles += 1

print(num_of_triangles)