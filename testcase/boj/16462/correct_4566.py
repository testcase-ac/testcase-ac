n=int(input())
print(round(sum(min(100,int(input().replace('0','9').replace('6','9')))for i in range(n))/n+1e-9))
