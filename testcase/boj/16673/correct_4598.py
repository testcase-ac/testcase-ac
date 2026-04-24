c,k,p=map(int,input().split())
print(sum(k*i+p*i*i for i in range(c+1)))
