from sys import stdin, stdout
input = stdin.readline
print = stdout.write
n = int(input())
for i in range(n):
    a,b=map(int,input().split())
    print('Case %d: %d\n' % (i+1,a+b))
