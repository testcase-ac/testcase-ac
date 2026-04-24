t = int(input())
for _ in range(t):
    ls = list(filter(lambda l: l%2==0, map(int,input().split())))
    print(sum(ls), min(ls))
