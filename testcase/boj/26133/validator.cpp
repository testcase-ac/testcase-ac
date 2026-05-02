#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    double x, y;
};

double cross(const Pt &a, const Pt &b, const Pt &c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

double crossVec(const Pt &a, const Pt &b) {
    return a.x*b.y - a.y*b.x;
}

double dotVec(const Pt &a, const Pt &b) {
    return a.x*b.x + a.y*b.y;
}

bool onSegment(const Pt &a, const Pt &b, const Pt &p) {
    // assume collinear check done before calling if needed
    return min(a.x,b.x) <= p.x + 1e-9 && p.x <= max(a.x,b.x) + 1e-9 &&
           min(a.y,b.y) <= p.y + 1e-9 && p.y <= max(a.y,b.y) + 1e-9;
}

bool segProperIntersect(const Pt &a, const Pt &b, const Pt &c, const Pt &d) {
    double c1 = cross(a,b,c);
    double c2 = cross(a,b,d);
    double c3 = cross(c,d,a);
    double c4 = cross(c,d,b);

    if ((c1 == 0 && onSegment(a,b,c)) ||
        (c2 == 0 && onSegment(a,b,d)) ||
        (c3 == 0 && onSegment(c,d,a)) ||
        (c4 == 0 && onSegment(c,d,b)))
        return true;

    return (c1 > 0 && c2 < 0 || c1 < 0 && c2 > 0) &&
           (c3 > 0 && c4 < 0 || c3 < 0 && c4 > 0);
}

bool segmentsTouchOrIntersect(const Pt &a, const Pt &b, const Pt &c, const Pt &d) {
    // including touching
    auto orient = [&](const Pt &p, const Pt &q, const Pt &r)->int{
        double v = cross(p,q,r);
        if (v > 1e-9) return 1;
        if (v < -1e-9) return -1;
        return 0;
    };
    int o1 = orient(a,b,c);
    int o2 = orient(a,b,d);
    int o3 = orient(c,d,a);
    int o4 = orient(c,d,b);

    if (o1 == 0 && onSegment(a,b,c)) return true;
    if (o2 == 0 && onSegment(a,b,d)) return true;
    if (o3 == 0 && onSegment(c,d,a)) return true;
    if (o4 == 0 && onSegment(c,d,b)) return true;

    return (o1*o2 < 0 && o3*o4 < 0);
}

bool pointOnLine(const Pt &a, const Pt &b, const Pt &p) {
    return fabs(cross(a,b,p)) <= 1e-9;
}

bool pointOnSegment(const Pt &a, const Pt &b, const Pt &p) {
    if (!pointOnLine(a,b,p)) return false;
    return onSegment(a,b,p);
}

bool pointInSimplePolygonStrict(const vector<Pt> &poly, const Pt &p) {
    // exclude boundary. standard ray casting.
    int n = (int)poly.size();
    for (int i = 0; i < n; ++i) {
        Pt a = poly[i];
        Pt b = poly[(i+1)%n];
        if (pointOnSegment(a,b,p)) return false; // on boundary not allowed
    }
    bool inside = false;
    for (int i = 0, j = n-1; i < n; j = i++) {
        const Pt &a = poly[i];
        const Pt &b = poly[j];
        bool intersect = ((a.y > p.y) != (b.y > p.y)) &&
                         (p.x < (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x);
        if (intersect) inside = !inside;
    }
    return inside;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100, "n");
    inf.readEoln();

    vector<Pt> poly(n);
    vector<pair<long long,long long>> ip(n);

    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(0LL, 1000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(0LL, 1000LL, "y_i");
        inf.readEoln();
        poly[i] = Pt{double(x), double(y)};
        ip[i] = {x,y};
    }

    // vertices distinct
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            ensuref(!(ip[i].first == ip[j].first && ip[i].second == ip[j].second),
                    "Polygon vertices %d and %d are identical (%lld, %lld)",
                    i, j, ip[i].first, ip[i].second);
        }
    }

    // simple polygon: no two non-consecutive edges intersect or touch
    for (int i = 0; i < n; ++i) {
        int ni = (i+1)%n;
        Pt a = poly[i], b = poly[ni];
        for (int j = i+1; j < n; ++j) {
            int nj = (j+1)%n;
            // skip if edges share a vertex (consecutive or same)
            if (i == j || i == nj || ni == j || ni == nj) continue;
            Pt c = poly[j], d = poly[nj];
            ensuref(!segmentsTouchOrIntersect(a,b,c,d),
                    "Edges (%d,%d) and (%d,%d) intersect or touch", i, ni, j, nj);
        }
    }

    // no two consecutive edges are collinear
    for (int i = 0; i < n; ++i) {
        int j = (i+1)%n;
        int k = (i+2)%n;
        double cr = cross(poly[i], poly[j], poly[k]);
        ensuref(fabs(cr) > 1e-9,
                "Consecutive edges (%d,%d) and (%d,%d) are collinear", i, j, j, k);
    }

    // area non-zero (implied by simplicity and non-collinearity, but double-check)
    long double area2 = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i+1)%n;
        area2 += (long double)poly[i].x*poly[j].y - (long double)poly[i].y*poly[j].x;
    }
    ensuref(fabsl(area2) > 0, "Polygon has zero area");

    // CCW order: as given
    ensuref(area2 > 0, "Polygon vertices must be in counterclockwise order");

    // read guard point
    long long gx = inf.readLong(0LL, 1000LL, "x_g");
    inf.readSpace();
    long long gy = inf.readLong(0LL, 1000LL, "y_g");
    inf.readEoln();
    Pt g{double(gx), double(gy)};

    // read sculpture center
    long long sx = inf.readLong(0LL, 1000LL, "x_s");
    inf.readSpace();
    long long sy = inf.readLong(0LL, 1000LL, "y_s");
    inf.readEoln();
    Pt s{double(sx), double(sy)};

    // guard and sculpture distinct
    ensuref(!(gx == sx && gy == sy),
            "Guard and sculpture positions must be distinct");

    // both strictly inside polygon
    ensuref(pointInSimplePolygonStrict(poly, g),
            "Guard position is not strictly inside the polygon");
    ensuref(pointInSimplePolygonStrict(poly, s),
            "Sculpture position is not strictly inside the polygon");

    inf.readEof();
}
