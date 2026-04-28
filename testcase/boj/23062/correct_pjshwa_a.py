def exgcd(a, b):
    s = 0; olds = 1
    t = 1; oldt = 0
    r = b; oldr = a
    while r:
        q = oldr // r
        oldr, r = r, oldr-q*r
        olds, s = s, olds-q*s
        oldt, t = t, oldt-q*t
    return oldr, olds, oldt

# solve n = a1 mod n1, a2 mod n2
# return n = A mod N
def CRT2(a1, n1, a2, n2):
    d, xp, yp = exgcd(n1, n2)
    if (a1-a2)%d: return None, None
    k1 = -xp*(a1-a2)//d
    lcm = n1*n2//d
    ans = (a1 + k1*n1) % lcm
    assert ans%n1 == a1 and ans%n2 == a2
    return ans, lcm

def CRT3(a1, n1, a2, n2, a3, n3):
    a, n = CRT2(a1, n1, a2, n2)
    if a == None: return None, None
    return CRT2(a, n, a3, n3)

input = __import__('sys').stdin.readline
MIS = lambda: map(int,input().split())
for TEST in range(int(input())):
    A, B, C, a, b, c = MIS()
    a, n = CRT3(a, A, b, B, c, C)
    print(-1 if a == None else a)
