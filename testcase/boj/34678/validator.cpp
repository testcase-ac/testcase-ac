#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long double dist(const Point &a, const Point &b) {
    long double dx = (long double)a.x - (long double)b.x;
    long double dy = (long double)a.y - (long double)b.y;
    return sqrtl(dx * dx + dy * dy);
}

// Check if three points are collinear
bool collinear(const Point &a, const Point &b, const Point &c) {
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    __int128 cross = (__int128)x1 * y2 - (__int128)y1 * x2;
    return cross == 0;
}

// Check for proper intersection between segments ab and cd (excluding shared endpoints)
int sgn(long long x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
}

long long cross(const Point &a, const Point &b, const Point &c) {
    // (b - a) x (c - a)
    return (b.x - a.x) * 1LL * (c.y - a.y) - (b.y - a.y) * 1LL * (c.x - a.x);
}

bool onSegment(const Point &a, const Point &b, const Point &p) {
    if (cross(a, b, p) != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool properIntersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    // Allow touching at endpoints only if they are shared endpoints of adjacent segments;
    // this function is used only for non-adjacent segments.
    long long c1 = cross(a, b, c);
    long long c2 = cross(a, b, d);
    long long c3 = cross(c, d, a);
    long long c4 = cross(c, d, b);

    int s1 = sgn(c1);
    int s2 = sgn(c2);
    int s3 = sgn(c3);
    int s4 = sgn(c4);

    if (s1 == 0 && onSegment(a, b, c)) return true;
    if (s2 == 0 && onSegment(a, b, d)) return true;
    if (s3 == 0 && onSegment(c, d, a)) return true;
    if (s4 == 0 && onSegment(c, d, b)) return true;

    return ( ( (__int128)c1 * c2 < 0 ) && ( (__int128)c3 * c4 < 0 ) );
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    vector<Point> v(n);
    for (int i = 0; i < n; ++i) {
        v[i].x = inf.readLong(-100000LL, 100000LL, "x_i");
        inf.readSpace();
        v[i].y = inf.readLong(-100000LL, 100000LL, "y_i");
        inf.readEoln();
    }

    // x(v_i) <= x(v_{i+1})
    for (int i = 0; i + 1 < n; ++i) {
        ensuref(v[i].x <= v[i+1].x,
                "x(v_%d) = %lld must be <= x(v_%d) = %lld",
                i+1, v[i].x, i+2, v[i+1].x);
    }

    // no two vertices at the same position
    {
        // use hashmap-like via sort
        vector<pair<long long,long long>> pts(n);
        for (int i = 0; i < n; ++i) pts[i] = {v[i].x, v[i].y};
        sort(pts.begin(), pts.end());
        for (int i = 0; i + 1 < n; ++i) {
            ensuref(!(pts[i].first == pts[i+1].first && pts[i].second == pts[i+1].second),
                    "Two vertices share the same position (%lld, %lld)",
                    pts[i].first, pts[i].second);
        }
    }

    // every segment has positive length
    for (int i = 0; i + 1 < n; ++i) {
        bool same = (v[i].x == v[i+1].x && v[i].y == v[i+1].y);
        ensuref(!same, "Segment (%d, %d) has zero length", i+1, i+2);
    }

    // no two segments intersect, except at their endpoints
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = i + 2; j + 1 < n; ++j) {
            // segments (i, i+1) and (j, j+1)
            // They share endpoint only if |i-j| == 1, which we excluded by j>=i+2
            // So any intersection is invalid.
            if (properIntersect(v[i], v[i+1], v[j], v[j+1])) {
                ensuref(false,
                        "Segments (%d,%d)-(%d,%d) and (%d,%d)-(%d,%d) improperly intersect",
                        i+1, i+2, v[i].x, v[i].y,
                        j+1, j+2, v[j].x, v[j].y);
            }
        }
    }

    // Verify that the polygonal path is "simple" in the sense above and that
    // the diameter (max path distance along P) is finite and computable in double.
    // We compute the total path length and ensure it fits in long double safely.
    vector<long double> pref(n);
    pref[0] = 0.0L;
    for (int i = 1; i < n; ++i) {
        long double d = dist(v[i-1], v[i]);
        ensuref(d > 0.0L, "Segment length must be positive between vertices %d and %d", i, i+1);
        pref[i] = pref[i-1] + d;
    }
    long double totalLen = pref.back();
    ensuref(isfinite((long double)totalLen), "Total path length is not finite");

    // The diameter along the path (without bridge) is totalLen,
    // since distance along path between endpoints is totalLen and
    // no shorter alternative paths exist (it's a simple path).
    // This must be >= any distance between inner points, trivially,
    // but we just ensure non-negativity and finiteness.
    ensuref(totalLen > 0.0L, "Total path length must be positive");
    ensuref(isfinite(totalLen), "Diameter is not finite");

    inf.readEof();
}
