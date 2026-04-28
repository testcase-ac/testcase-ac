import sys;r=sys.stdin.readline;t=int(r())
for _ in range(t):
	n=int(r())
	indx = 0
	while n!=0:
		if n%2==1:print(indx,end=" ")
		n//=2;indx+=1
	print()
