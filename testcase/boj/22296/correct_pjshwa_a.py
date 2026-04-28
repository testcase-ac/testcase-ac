from fractions import Fraction
from math import gcd

def divisors(n):
    for d in range(1, n+1):
        if d*d > n: return
        if d*d == n: yield d; continue
        if n%d: continue
        yield d
        yield n//d

def candidate(a0, an):
    assert a0 and an
    dq = list(divisors(abs(an)))
    for p in divisors(abs(a0)):
        for q in dq:
            if abs(gcd(p, q)) != 1: continue
            yield (p, q)
            yield (-p, q)
    yield (0, 1)
    
# ax + b = 0
def solve_linear(a, b):
    if a == 0: return set()
    return {(-b, a)}

# ax^2 + bx + c = 0
def solve_quadratic(a, b, c):
    if a == 0: return solve_linear(b, c)
    if c == 0: return solve_linear(a, b) | {(0, 1)}
    ans = set()
    for p, q in candidate(c, a):
        # x = p/q
        if a*p*p + b*p*q + c*q*q == 0: ans.add((p, q))
    return ans    

# ax^3 + bx^2 + cx + d = 0
def solve_cubic(a, b, c, d):
    if a == 0: return solve_quadratic(b, c, d)
    if d == 0: return solve_quadratic(a, b, c) | {(0, 1)}
    ans = set()
    for p, q in candidate(d, a):
        # x = p/q
        if a*p*p*p + b*p*p*q + c*p*q*q + d*q*q*q == 0: ans.add((p, q))
    return ans

def P7(a,b,c,d):
    S = solve_cubic(a, b, c, d)
    return [T[0]/T[1] for T in S]
