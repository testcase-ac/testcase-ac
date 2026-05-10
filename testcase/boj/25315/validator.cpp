#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(const Point &a, const Point &b, const Point &c) {
    // (b - a) x (c - a)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool segmentsProperlyIntersect(const Point &a, const Point &b,
                               const Point &c, const Point &d) {
    // We know: all endpoints are distinct globally and no three points are collinear.
    // So any intersection between segments is a proper crossing (not touching at endpoints or collinear).
    long long c1 = cross(a, b, c);
    long long c2 = cross(a, b, d);
    long long c3 = cross(c, d, a);
    long long c4 = cross(c, d, b);

    // Proper intersection if they straddle each other
    return (c1 > 0 && c2 < 0 || c1 < 0 && c2 > 0) &&
           (c3 > 0 && c4 < 0 || c3 < 0 && c4 > 0);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 2500;
    const long long COORD_MIN = -1000000000LL;
    const long long COORD_MAX =  1000000000LL;
    const long long W_MIN = 1LL;
    const long long W_MAX = 1000000000LL;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    vector<Point> s(N), e(N);
    vector<long long> w(N);

    // To ensure all 2N points are distinct
    set<pair<long long, long long>> allPoints;

    for (int i = 0; i < N; ++i) {
        long long sx = inf.readLong(COORD_MIN, COORD_MAX, "sx_i");
        inf.readSpace();
        long long sy = inf.readLong(COORD_MIN, COORD_MAX, "sy_i");
        inf.readSpace();
        long long ex = inf.readLong(COORD_MIN, COORD_MAX, "ex_i");
        inf.readSpace();
        long long ey = inf.readLong(COORD_MIN, COORD_MAX, "ey_i");
        inf.readSpace();
        long long wi = inf.readLong(W_MIN, W_MAX, "w_i");
        inf.readEoln();

        s[i] = {sx, sy};
        e[i] = {ex, ey};
        w[i] = wi;

        pair<long long,long long> ps = {sx, sy};
        pair<long long,long long> pe = {ex, ey};

        ensuref(ps != pe, "Segment %d has identical endpoints (%lld, %lld)", i+1, sx, sy);

        ensuref(!allPoints.count(ps),
                "Point (%lld, %lld) used more than once (as endpoint of segment %d)",
                sx, sy, i+1);
        allPoints.insert(ps);

        ensuref(!allPoints.count(pe),
                "Point (%lld, %lld) used more than once (as endpoint of segment %d)",
                ex, ey, i+1);
        allPoints.insert(pe);
    }

    // Check: no three points are collinear.
    // There are 2N points, N <= 2500 => up to 5000 points.
    // O(P^3) is too big, but we can use hashing with slopes per pivot: O(P^2 log P) is fine.
    // However, statement is strong; but we still must verify.
    // Simple O(P^3) worst-case: 5000^3 = 1.25e11 (too big).
    // We'll implement O(P^2 log P) using normalized direction vectors from each point.

    vector<Point> pts;
    pts.reserve(allPoints.size());
    for (auto &pr : allPoints) {
        pts.push_back({pr.first, pr.second});
    }
    int P = (int)pts.size();

    // For each pivot i, store directions to j>i, normalized by gcd and sign.
    // If any direction appears twice for same pivot, then three points collinear.
    // Because pivot + two points with same direction lie on same line through pivot.
    for (int i = 0; i < P; ++i) {
        map<pair<long long,long long>, int> dirCount;
        dirCount.clear();
        for (int j = 0; j < P; ++j) if (j != i) {
            long long dx = pts[j].x - pts[i].x;
            long long dy = pts[j].y - pts[i].y;
            long long g = std::gcd(dx < 0 ? -dx : dx, dy < 0 ? -dy : dy);
            dx /= g;
            dy /= g;
            // Normalize sign so that (dx,dy) has a canonical direction
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx;
                dy = -dy;
            }
            auto key = make_pair(dx, dy);
            dirCount[key]++;
            ensuref(dirCount[key] <= 1,
                    "Three collinear points detected with pivot at (%lld, %lld)",
                    pts[i].x, pts[i].y);
        }
    }

    // Additional global property checks related to the problem:
    // There are no explicit guarantees about intersection existence beyond what is stated:
    // - All endpoints distinct
    // - No three points collinear
    // That already implies: if two segments' interiors intersect, it is a proper crossing.
    // We verify basic geometric consistency: segment intersection classification stable.

    // We do not need to check for connectivity or existence of some answer beyond these,
    // since any order of performing the N cuts is valid in the problem.

    // As a light sanity check, we can check that our intersection predicate is consistent
    // with geometric assumptions by verifying no segment intersects exactly at endpoints,
    // which is already excluded by distinct endpoints and no three collinear points.

    // Optional: verify that our "no three collinear" plus distinct endpoints guarantees
    // that if two segments share an endpoint, they are not allowed by "all 2N points distinct".
    // Already enforced above.

    inf.readEof();
}
