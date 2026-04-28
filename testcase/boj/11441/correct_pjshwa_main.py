import sys;r=sys.stdin.readline;r();sum_up_to=[0];s=0
for i in map(int,r().split()):
	s+=i;sum_up_to.append(s)
m=int(r())
for _ in range(m):
	i,j=map(int,r().split())
	print(sum_up_to[j]-sum_up_to[i-1])