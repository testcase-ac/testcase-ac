import sys;r=sys.stdin.readline;n=int(r())
for _ in range(n):
    l=list(filter(lambda x:x%2==0,map(int,r().split())));print("{} {}".format(sum(l),min(l)))