def convex4gon(L):
    def g(p,q,r):
        t=L[p][0]*(L[q][1]-L[r][1])+L[q][0]*(L[r][1]-L[p][1])+L[r][0]*(L[p][1]-L[q][1])
        return t//abs(t)
    n=len(L)
    R=0
    for a in range(n):
        for b in range(a):
            for c in range(b):
                for d in range(c):
                    if g(a,b,c)*g(b,c,d)*g(c,d,a)*g(d,a,b)==1:
                        R+=1
    return R
