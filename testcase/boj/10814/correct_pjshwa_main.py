import sys
n = int(input())
l = []
for i in range(n):
    l.append((i, sys.stdin.readline().rstrip().split()))
l.sort(key = lambda x: (int(x[1][0]), x[0]))
for i in l:
    print(i[1][0], i[1][1])