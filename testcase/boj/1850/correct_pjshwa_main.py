def gcd(a, b):
	while b != 0:
		a, b = b, a % b
	return a

import sys
r = sys.stdin.readline
print("1" * gcd(*map(int, r().split())), end="")