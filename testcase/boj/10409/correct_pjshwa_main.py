import sys;r=sys.stdin.readline
n,t=map(int,r().split());works=map(int,r().split())
s=0
for i,work in enumerate(works):
    if s+work<=t: s+=work
    else:print(i);break
else:print(n)