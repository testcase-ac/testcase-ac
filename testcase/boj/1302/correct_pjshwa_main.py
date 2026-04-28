import sys
n = int(input())
d = {}
for i in range(n):
    s = sys.stdin.readline().rstrip('\n')
    if s in d: d[s] += 1
    else: d[s] = 1

d = sorted(d.items(), key=lambda x: (-x[1], x[0]))
print(d[0][0])