#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(long long ax, long long ay, long long bx, long long by) {
    __int128 v = (__int128)ax * by - (__int128)ay * bx;
    // Value always fits in signed 128-bit; we cast back to long long.
    return (long long)v;
}

int sgn(long long v) {
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

bool onSegment(const Point &a, const Point &b, const Point &p) {
    // assume p is collinear with a-b
    if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x)) return false;
    if (p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) return false;
    return true;
}

// Avoid conflict with std::relation concept by using a different name
int segmentRelation(const Point &a, const Point &b, const Point &c, const Point &d) {
    // 0: no intersection
    // 1: exactly one intersection, at least one endpoint
    // 2: exactly one intersection, not an endpoint of any
    // 3: infinitely many intersections (overlapping collinear)

    long long c1 = cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
    long long c2 = cross(b.x - a.x, b.y - a.y, d.x - a.x, d.y - a.y);
    long long c3 = cross(d.x - c.x, d.y - c.y, a.x - c.x, a.y - c.y);
    long long c4 = cross(d.x - c.x, d.y - c.y, b.x - c.x, b.y - c.y);

    int s1 = sgn(c1);
    int s2 = sgn(c2);
    int s3 = sgn(c3);
    int s4 = sgn(c4);

    // all four oriented area values zero -> collinear
    if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0) {
        long long minAx = min(a.x, b.x), maxAx = max(a.x, b.x);
        long long minCx = min(c.x, d.x), maxCx = max(c.x, d.x);
        long long minAy = min(a.y, b.y), maxAy = max(a.y, b.y);
        long long minCy = min(c.y, d.y), maxCy = max(c.y, d.y);

        bool interX = !(maxAx < minCx || maxCx < minAx);
        bool interY = !(maxAy < minCy || maxCy < minAy);
        if (!interX || !interY) return 0;

        bool aIn = onSegment(c, d, a);
        bool bIn = onSegment(c, d, b);
        bool cIn = onSegment(a, b, c);
        bool dIn = onSegment(a, b, d);

        vector<Point> common;
        if (aIn) common.push_back(a);
        if (bIn) common.push_back(b);
        if (cIn) common.push_back(c);
        if (dIn) common.push_back(d);

        sort(common.begin(), common.end(), [](const Point &p1, const Point &p2) {
            if (p1.x != p2.x) return p1.x < p2.x;
            return p1.y < p2.y;
        });
        common.erase(unique(common.begin(), common.end(), [](const Point &p1, const Point &p2) {
            return p1.x == p2.x && p1.y == p2.y;
        }), common.end());

        if (common.empty()) {
            // Should not really happen with finite segments, but treat as no intersection.
            return 0;
        } else if (common.size() == 1) {
            // Single common point (endpoint intersection)
            return 1;
        } else {
            // Overlapping segment (infinitely many)
            return 3;
        }
    }

    // Non-collinear case: check general segment intersection
    bool inter = (s1 * s2 <= 0) && (s3 * s4 <= 0);
    if (!inter) return 0;

    // Exactly one intersection point here.
    bool endpoint = (s1 == 0 || s2 == 0 || s3 == 0 || s4 == 0);
    return endpoint ? 1 : 2;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 2000, "N");
    inf.readEoln();

    vector<Point> A(N), B(N);

    for (int i = 0; i < N; ++i) {
        long long x1 = inf.readLong(-1000000000LL, 1000000000LL, "x1");
        inf.readSpace();
        long long y1 = inf.readLong(-1000000000LL, 1000000000LL, "y1");
        inf.readSpace();
        long long x2 = inf.readLong(-1000000000LL, 1000000000LL, "x2");
        inf.readSpace();
        long long y2 = inf.readLong(-1000000000LL, 1000000000LL, "y2");
        inf.readEoln();

        ensuref(!(x1 == x2 && y1 == y2),
                "segment %d has zero length (both endpoints equal)", i + 1);

        A[i] = {x1, y1};
        B[i] = {x2, y2};
    }

    // Sanity: all pair relations are computable according to problem's definition.
    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            (void)segmentRelation(A[i], B[i], A[j], B[j]);
        }
    }

    inf.readEof();
}
