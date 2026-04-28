import sys
d = dict(zip(['A','B','C'],sorted(list(map(int,sys.stdin.readline().rstrip().split())))))
for s in sys.stdin.readline().rstrip():
    print(d[s], end=" ")