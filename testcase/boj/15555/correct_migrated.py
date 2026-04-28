n,m=map(int,input().split())
l=[]
for i in range(n):l.append(input()+'0')
l.append('0'*(m+1))
d0=[[0]*(m+1) for i in range(n+1)]
dh=[[0]*(m+1) for i in range(n+1)]
dv=[[0]*(m+1) for i in range(n+1)]
ans=0
for s in range(m+n-1):
    M=0
    for i in range(s+1):
        j=s-i
        if j>=m:continue
        d0[i][j]=max(d0[i-1][j+1],dv[i-1][j+1],dh[i-1][j+1])
        dv[i][j]=max(d0[i-1][j+1],dv[i-1][j+1])
        dh[i][j]=max(d0[i-1][j+1],dh[i-1][j+1])
        if l[i][j-1]+l[i][j]+l[i][j+1]=='RGW':dh[i][j]+=1
        if l[i-1][j]+l[i][j]+l[i+1][j]=='RGW':dv[i][j]+=1
        if i+1>=n:break
    M=max(d0[i][j],dv[i][j],dh[i][j])
    ans+=M
    #print(M)

print(ans)
