import itertools


def ccw(p1, p2, p3):
    return (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p3[0] - p1[0]) * (p2[1] - p1[1])


def is_convex_quadrilateral(points):
    points = sorted(points)
    p0, p1, p2, p3 = points
    if ccw(p0, p1, p2) * ccw(p0, p1, p3) < 0 and ccw(p2, p3, p0) * ccw(p2, p3, p1) < 0:
        return True
    if ccw(p0, p2, p1) * ccw(p0, p2, p3) < 0 and ccw(p1, p3, p0) * ccw(p1, p3, p2) < 0:
        return True
    if ccw(p0, p3, p1) * ccw(p0, p3, p2) < 0 and ccw(p1, p2, p0) * ccw(p1, p2, p3) < 0:
        return True
    return False


def convex4gon(L):
    ret = 0
    for comb in itertools.combinations(L, 4):
        if is_convex_quadrilateral(comb):
            ret += 1
    return ret
