import sys;r=sys.stdin.readline;n,m=map(int,r().split());cows=0;mult=1
while n%2!=0 and m%2!=0:n//=2;m//=2;cows+=mult;mult*=4
print(cows)