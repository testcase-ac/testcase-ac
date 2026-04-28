import sys;r=sys.stdin.readline
n,m,k=map(int,r().split());teams=0
while n+m>=k+3 and n>=2 and m>=1:
    n-=2;m-=1;teams+=1
print(teams)