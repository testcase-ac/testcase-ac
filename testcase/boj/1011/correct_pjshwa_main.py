import sys;r=sys.stdin.readline;n=int(r())
for _ in range(n):
	x,y=map(int,r().split());sq=int((y-x-1)**0.5)
	if y-x>sq*sq+sq:print(2*sq+1)
	else:print(2*sq)