import sys
r = sys.stdin.readline
l, p = map(int, r().split())
for item in map(lambda x: int(x)-l*p, r().split()):
    print(item, end=" ")