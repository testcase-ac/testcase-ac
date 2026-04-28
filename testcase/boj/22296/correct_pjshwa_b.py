def gcd(x,y):
    while y != 0:
        x,y = y,x%y
    return x
def P7(a,b,c,d):
    L = [a,b,c,d]
    j = 0
    k = 3
    while L[j] == 0:
        j += 1
    while L[k] == 0:
        k -= 1
    P = []
    Q = []
    R = []
    i = 1
    n = abs(L[k])
    while i*i <= n:
        if n%i == 0:
            P.append(i)
            if i*i != n:
                P.append(n//i)
        i += 1
    i = 1
    n = abs(L[j])
    while i*i <= n:
        if n%i == 0:
            Q.append(i)
            if i*i != n:
                Q.append(n//i)
        i += 1
    for p in P:
        for q in Q:
            if gcd(p,q) == 1:
                if a*p*p*p + b*p*p*q + c*p*q*q + d*q*q*q == 0:
                    R.append(p/q)
                if a*p*p*p - b*p*p*q + c*p*q*q - d*q*q*q == 0:
                    R.append(-p/q)
    if d == 0:
        R.append(0.0)
    return R
