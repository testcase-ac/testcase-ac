import sys
a, b = sys.stdin.readline().rstrip().split()
a_i = 0
b_i = 0
for i in a:
	a_i += int(i)
for i in b:
	b_i += int(i)
print(a_i*b_i)