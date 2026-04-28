import sys
a, b = map(int, sys.stdin.readline().split())

def sigma(a, b):
	if a > b:
		a, b = b, a
	return b*(b+1)//2 - a*(a-1)//2

print(sigma(a,b))
