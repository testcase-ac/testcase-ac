n,m = map(int,input().split())
s = str(n)*n
print(s if len(s) <= m else s[:m])
