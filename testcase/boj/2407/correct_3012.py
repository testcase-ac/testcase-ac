ans = 1
n,m = map(int,input().split())
for i in range(1,n+1):
    ans *= i
for i in range(1,m+1):
    ans //= i
for i in range(1,(n-m)+1):
    ans //= i
print(ans)
