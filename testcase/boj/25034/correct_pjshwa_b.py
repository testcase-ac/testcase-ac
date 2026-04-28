def ccw(p1, p2, p3):
    # positive -> ccw; negative -> cw; 0 -> collinear
    return (p2[0]-p1[0])*(p3[1]-p1[1]) - (p2[1]-p1[1])*(p3[0]-p1[0])

from itertools import permutations
def convex4gon(L):
    cnt = 0
    for a,b,c,d in permutations(L, 4):
        sign = [ccw(a,b,c), ccw(b,c,d), ccw(c,d,a), ccw(d,a,b)]
        cnt+= max(sign) < 0
    return cnt//4
