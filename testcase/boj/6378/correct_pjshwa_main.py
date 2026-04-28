def digital_root(number):
	return sum(map(int, list(str(number))))

import sys;r=sys.stdin.readline;n=int(r())
while n!=0:
	while n//10!=0:n=digital_root(n)
	print(n);n=int(r())