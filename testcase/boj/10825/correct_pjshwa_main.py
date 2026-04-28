import sys
n = int(input())
l = []
for i in range(n):
    l.append(sys.stdin.readline().rstrip('\n').split())
    
for i in sorted(l, key=lambda x: (-int(x[1]),int(x[2]),-int(x[3]),x[0])):
    print(i[0])