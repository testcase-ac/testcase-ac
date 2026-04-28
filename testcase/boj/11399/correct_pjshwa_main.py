n=int(input())
import sys
r=sys.stdin.readline
l = sorted(map(int, r().split()))
for i in range(1, len(l)):
    l[i] += l[i-1]
print(sum(l))