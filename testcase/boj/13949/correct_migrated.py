k,n=map(int,input().split())
s={(0,1,k)}
u=[0]
while n:
    t=s.copy()
    for a,b,c in s:
        if a!=b and b!=c:
            if a not in u and b not in u and c not in u:
                u+=[a,b,c]
                print(a,b,c)
                n-=1
                if n==0: exit()
            for _ in range(3):
                x=k*(a+b)-c
                if x>=0: t.add(tuple(sorted((a,b,x))))
                a,b,c=b,c,a
    s=t
