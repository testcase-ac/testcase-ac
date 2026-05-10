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

int sgn(long long v) {
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

// Check that polygon is strictly convex and CCW, and non-degenerate
void validateConvexCCW(const vector<Point> &p, const string &name) {
    int n = (int)p.size();
    ensuref(n >= 3, "%s must have at least 3 vertices", name.c_str());

    // No consecutive duplicate vertices, no all-collinear polygon, strictly convex
    int dir = 0;
    long long area2 = 0;
    for (int i = 0; i < n; ++i) {
        const Point &a = p[i];
        const Point &b = p[(i + 1) % n];
        const Point &c = p[(i + 2) % n];

        ensuref(!(a.x == b.x && a.y == b.y),
                "%s has duplicate consecutive vertices at index %d and %d",
                name.c_str(), i, (i + 1) % n);

        long long cr = cross(a, b, c);
        int s = sgn(cr);
        if (s != 0) {
            if (dir == 0) dir = s;
            else ensuref(dir == s,
                         "%s is not strictly convex or not consistently oriented at index %d",
                         name.c_str(), i);
        }
        // For area (shoelace)
        area2 += a.x * b.y - b.x * a.y;
    }
    ensuref(dir != 0, "%s is degenerate (all points collinear)", name.c_str());
    // CCW: area2 should be > 0
    ensuref(area2 > 0, "%s vertices must be given in counter-clockwise order", name.c_str());
}

// Check that polygon B is strictly inside polygon A (including boundary not allowed)
// for all vertices of B. The statement says blue convex polygon is "완전하게 포함":
// we interpret as its boundary lies strictly inside red polygon, i.e., no touching.
bool pointInConvexStrict(const vector<Point> &poly, const Point &p) {
    int n = (int)poly.size();
    for (int i = 0; i < n; ++i) {
        const Point &a = poly[i];
        const Point &b = poly[(i + 1) % n];
        long long cr = cross(a, b, p);
        if (cr <= 0) return false; // on boundary or outside (for CCW polygon)
    }
    return true;
}

// Non-strict (inside or on boundary)
bool pointInConvexNonStrict(const vector<Point> &poly, const Point &p) {
    int n = (int)poly.size();
    for (int i = 0; i < n; ++i) {
        const Point &a = poly[i];
        const Point &b = poly[(i + 1) % n];
        long long cr = cross(a, b, p);
        if (cr < 0) return false; // outside
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(3, 100000, "M");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    vector<Point> red(N), blue(M);

    for (int i = 0; i < N; ++i) {
        long long a = inf.readLong(-1000000LL, 1000000LL, "A_i");
        inf.readSpace();
        long long b = inf.readLong(-1000000LL, 1000000LL, "B_i");
        inf.readEoln();
        red[i] = {a, b};
    }

    for (int i = 0; i < M; ++i) {
        long long c = inf.readLong(-1000000LL, 1000000LL, "C_i");
        inf.readSpace();
        long long d = inf.readLong(-1000000LL, 1000000LL, "D_i");
        inf.readEoln();
        blue[i] = {c, d};
    }

    // Validate convexity, orientation, non-degeneracy
    validateConvexCCW(red, "red polygon");
    validateConvexCCW(blue, "blue polygon");

    // Validate that blue polygon is strictly inside red polygon (no touching)
    for (int i = 0; i < M; ++i) {
        ensuref(pointInConvexStrict(red, blue[i]),
                "blue polygon vertex %d is not strictly inside red polygon", i);
    }

    // Read queries and also check that they are independent in the sense that
    // statement's conditions about classification are well-defined.
    // There is no additional global constraint except ranges,
    // but we can cheaply check canonical polygon-related promises:
    // - if candle is outside or on boundary of red, solution prints "OUT".
    // - if inside or on boundary of blue, prints "IN".
    // There is no promise that every query satisfies any extra property,
    // so we just validate number ranges and format.
    for (int i = 0; i < Q; ++i) {
        long long x = inf.readLong(-1000000LL, 1000000LL, "X_i");
        inf.readSpace();
        long long y = inf.readLong(-1000000LL, 1000000LL, "Y_i");
        inf.readEoln();

        (void)x;
        (void)y;
        // No further constraints on (x, y) from statement.
    }

    inf.readEof();
}
