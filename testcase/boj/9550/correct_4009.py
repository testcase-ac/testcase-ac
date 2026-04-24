T = int(input())
for i in range(T):
    n,k = map(int,input().split())
    print(sum(i//k for i in map(int,input().split())))
