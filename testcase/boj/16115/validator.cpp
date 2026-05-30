#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

struct Point {
    int64 x;
    int64 y;
};

static i128 cross(Point a, Point b) {
    return (i128)a.x * b.y - (i128)a.y * b.x;
}

static i128 cross(Point a, Point b, Point c) {
    return cross({b.x - a.x, b.y - a.y}, {c.x - a.x, c.y - a.y});
}

static int half(Point p) {
    return p.y > 0 || (p.y == 0 && p.x >= 0) ? 0 : 1;
}

static bool polarLess(Point a, Point b) {
    int ha = half(a), hb = half(b);
    if (ha != hb) return ha < hb;
    i128 cr = cross(a, b);
    if (cr != 0) return cr > 0;
    return (i128)a.x * a.x + (i128)a.y * a.y < (i128)b.x * b.x + (i128)b.y * b.y;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 300000, "N");
    inf.readEoln();

    vector<Point> p(n);
    set<pair<int64, int64>> seen;
    for (int i = 0; i < n; ++i) {
        p[i].x = inf.readLong(-1000000LL, 1000000LL, "x_i");
        inf.readSpace();
        p[i].y = inf.readLong(-1000000LL, 1000000LL, "y_i");
        inf.readEoln();
        ensuref(seen.insert({p[i].x, p[i].y}).second,
                "duplicate vertex at index %d: (%lld, %lld)", i + 1, p[i].x, p[i].y);
    }

    i128 area2 = 0;
    for (int i = 0; i < n; ++i) {
        Point a = p[i];
        Point b = p[(i + 1) % n];
        area2 += cross(a, b);
        ensuref(cross(a, b) >= 0,
                "origin is outside the polygon kernel at edge %d", i + 1);
    }
    ensuref(area2 > 0, "polygon vertices must be given in counterclockwise order");

    for (int i = 0; i < n; ++i) {
        Point a = p[i];
        Point b = p[(i + 1) % n];
        Point c = p[(i + 2) % n];
        ensuref(cross(a, b, c) != 0,
                "three consecutive vertices are collinear at indices %d, %d, %d",
                i + 1, (i + 1) % n + 1, (i + 2) % n + 1);
    }

    int first = 0;
    for (int i = 1; i < n; ++i) {
        if (polarLess(p[i], p[first])) first = i;
    }

    bool hasPositiveStep = false;
    for (int k = 0; k + 1 < n; ++k) {
        int i = (first + k) % n;
        int j = (first + k + 1) % n;
        ensuref(!polarLess(p[j], p[i]),
                "vertices are not in counterclockwise radial order at edge %d", i + 1);
        hasPositiveStep = hasPositiveStep || cross(p[i], p[j]) > 0;
    }
    ensuref(hasPositiveStep, "polygon must make a positive counterclockwise turn");

    inf.readEof();
    return 0;
}
