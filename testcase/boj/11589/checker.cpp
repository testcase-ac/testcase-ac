#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

struct IPoint {
    int x, y;
};

long long cross(const IPoint &a, const IPoint &b, const IPoint &c) {
    // cross of (b-a) x (c-a)
    return (long long)(b.x - a.x) * (c.y - a.y) - (long long)(b.y - a.y) * (c.x - a.x);
}

bool onSegment(const IPoint &a, const IPoint &b, const IPoint &p) {
    if (cross(a, b, p) != 0) return false;
    if (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x)
     && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y))
        return true;
    return false;
}

bool segIntersect(const IPoint &a, const IPoint &b, const IPoint &c, const IPoint &d) {
    long long c1 = cross(a, b, c);
    long long c2 = cross(a, b, d);
    long long c3 = cross(c, d, a);
    long long c4 = cross(c, d, b);
    if (c1 > 0 && c2 < 0 || c1 < 0 && c2 > 0) {
        if (c3 > 0 && c4 < 0 || c3 < 0 && c4 > 0)
            return true;
    }
    // check colinear/touching
    if (c1 == 0 && onSegment(a, b, c)) return true;
    if (c2 == 0 && onSegment(a, b, d)) return true;
    if (c3 == 0 && onSegment(c, d, a)) return true;
    if (c4 == 0 && onSegment(c, d, b)) return true;
    return false;
}

// point in convex polygon including boundary
bool pointInPoly(const vector<Point> &P, const Point &pt) {
    int m = P.size();
    int sign = 0;
    for (int i = 0; i < m; i++) {
        const Point &a = P[i];
        const Point &b = P[(i+1)%m];
        // orientation of a->b->pt
        double cr = (b.x - a.x)*(pt.y - a.y) - (b.y - a.y)*(pt.x - a.x);
        if (fabs(cr) < 1e-9) continue;
        int s = cr > 0 ? 1 : -1;
        if (sign == 0) sign = s;
        else if (sign != s) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int N = inf.readInt();
    vector<IPoint> A(N), B(N);
    for (int i = 0; i < N; i++) {
        A[i].x = inf.readInt();
        A[i].y = inf.readInt();
        B[i].x = inf.readInt();
        B[i].y = inf.readInt();
    }
    // read contestant output
    vector<int> order;
    order.reserve(N);
    for (int i = 0; i < N; i++) {
        if (ouf.eof())
            ouf.quitf(_wa, "not enough sticks in output (found %d, expected %d)", i, N);
        int x = ouf.readInt();
        if (x < 1 || x > N)
            ouf.quitf(_wa, "stick label %d at position %d is out of range [1, %d]", x, i+1, N);
        order.push_back(x-1);
    }
    // no extra tokens
    ouf.skipBlanks();
    if (!ouf.eof())
        ouf.quitf(_wa, "extra data after reading %d stick labels", N);
    // permutation check
    vector<char> seen(N, 0);
    for (int i = 0; i < N; i++) {
        if (seen[order[i]])
            ouf.quitf(_wa, "stick %d appears more than once", order[i]+1);
        seen[order[i]] = 1;
    }
    for (int i = 0; i < N; i++) {
        if (!seen[i])
            ouf.quitf(_wa, "stick %d is missing in output", i+1);
    }
    // precompute sweep polygon for each stick
    vector<vector<Point>> poly(N);
    for (int i = 0; i < N; i++) {
        int x1 = A[i].x, y1 = A[i].y;
        int x2 = B[i].x, y2 = B[i].y;
        int y_max = max(y1, y2);
        // corners of Minkowski sum of segment with vertical [0, -y_max]
        vector<Point> P(4);
        P[0] = Point{double(x1), double(y1)};
        P[1] = Point{double(x2), double(y2)};
        P[2] = Point{double(x2), double(y2 - y_max)};
        P[3] = Point{double(x1), double(y1 - y_max)};
        // sort ccw around center
        Point center{0,0};
        for (int j = 0; j < 4; j++) {
            center.x += P[j].x;
            center.y += P[j].y;
        }
        center.x /= 4.0;
        center.y /= 4.0;
        sort(P.begin(), P.end(), [&](const Point &a, const Point &b){
            double ang1 = atan2(a.y - center.y, a.x - center.x);
            double ang2 = atan2(b.y - center.y, b.x - center.x);
            return ang1 < ang2;
        });
        poly[i] = P;
    }
    vector<char> removed(N, 0);
    // simulate removals
    for (int step = 0; step < N; step++) {
        int s = order[step];
        // check no remaining stick blocks s
        for (int j = 0; j < N; j++) {
            if (j == s || removed[j]) continue;
            // does segment j intersect poly[s] ?
            // check edge intersections
            bool bad = false;
            // segment j endpoints
            IPoint c = A[j], d = B[j];
            // check intersection with each poly edge
            for (int e = 0; e < 4 && !bad; e++) {
                Point p1 = poly[s][e];
                Point p2 = poly[s][(e+1)%4];
                // convert p1,p2 to IPoint approximately by rounding? Actually p1,p2 have integer x but double y.
                // But segIntersect only uses integer coords. Instead do segment-segment intersect in double?
                // We'll do segment intersection in double for this check.
                // Mode: use robust line intersection in double:
                auto orientD = [&](const Point &a, const Point &b, const Point &pt){
                    return (b.x - a.x)*(pt.y - a.y) - (b.y - a.y)*(pt.x - a.x);
                };
                // bounding boxes
                double minx1 = min(double(c.x), double(d.x)), maxx1 = max(double(c.x), double(d.x));
                double miny1 = min(double(c.y), double(d.y)), maxy1 = max(double(c.y), double(d.y));
                double minx2 = min(p1.x, p2.x), maxx2 = max(p1.x, p2.x);
                double miny2 = min(p1.y, p2.y), maxy2 = max(p1.y, p2.y);
                if (maxx1 < minx2 - 1e-9 || maxx2 < minx1 - 1e-9 ||
                    maxy1 < miny2 - 1e-9 || maxy2 < miny1 - 1e-9)
                    continue;
                double c1 = orientD(Point{(double)c.x,(double)c.y}, Point{(double)d.x,(double)d.y}, p1);
                double c2 = orientD(Point{(double)c.x,(double)c.y}, Point{(double)d.x,(double)d.y}, p2);
                double c3 = orientD(p1, p2, Point{(double)c.x,(double)c.y});
                double c4 = orientD(p1, p2, Point{(double)d.x,(double)d.y});
                if (c1 * c2 < 0 && c3 * c4 < 0) {
                    bad = true; break;
                }
                auto onSegD = [&](const Point &aa, const Point &bb, const Point &pp){
                    if (fabs(orientD(aa,bb,pp)) > 1e-9) return false;
                    if (min(aa.x,bb.x) -1e-9 <= pp.x && pp.x <= max(aa.x,bb.x)+1e-9 &&
                        min(aa.y,bb.y) -1e-9 <= pp.y && pp.y <= max(aa.y,bb.y)+1e-9)
                        return true;
                    return false;
                };
                if (fabs(c1) < 1e-9 && onSegD(Point{(double)c.x,(double)c.y},Point{(double)d.x,(double)d.y},p1)) { bad=true; break; }
                if (fabs(c2) < 1e-9 && onSegD(Point{(double)c.x,(double)c.y},Point{(double)d.x,(double)d.y},p2)) { bad=true; break; }
                if (fabs(c3) < 1e-9 && onSegD(p1,p2,Point{(double)c.x,(double)c.y})) { bad=true; break; }
                if (fabs(c4) < 1e-9 && onSegD(p1,p2,Point{(double)d.x,(double)d.y})) { bad=true; break; }
            }
            if (bad) {
                ouf.quitf(_wa, "stick %d cannot be removed at step %d, blocked by stick %d",
                          s+1, step+1, j+1);
            }
            // check if either endpoint of j is inside poly[s]
            Point pj1{(double)c.x, (double)c.y}, pj2{(double)d.x, (double)d.y};
            if (pointInPoly(poly[s], pj1) || pointInPoly(poly[s], pj2)) {
                ouf.quitf(_wa, "stick %d cannot be removed at step %d, blocked by stick %d",
                          s+1, step+1, j+1);
            }
        }
        removed[s] = 1;
    }
    quitf(_ok, "valid removal order");
    return 0;
}
