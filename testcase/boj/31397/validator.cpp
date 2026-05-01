#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct P {
    long long x, y;
};

long double cross(const P &a, const P &b, const P &c) {
    return (long double)(b.x - a.x) * (c.y - a.y) -
           (long double)(b.y - a.y) * (c.x - a.x);
}

long double areaPolygon(const vector<P> &p) {
    int n = (int)p.size();
    long double s = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        s += (long double)p[i].x * p[j].y - (long double)p[i].y * p[j].x;
    }
    return fabsl(s) * 0.5L;
}

long double dist(const P &a, const P &b) {
    long double dx = (long double)b.x - a.x;
    long double dy = (long double)b.y - a.y;
    return sqrtl(dx * dx + dy * dy);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 200000, "N");
    inf.readEoln();

    vector<P> v(N);
    for (int i = 0; i < N; ++i) {
        long long x = inf.readLong(-10000000LL, 10000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-10000000LL, 10000000LL, "y_i");
        inf.readEoln();
        v[i] = {x, y};
    }

    // Basic polygon validations

    // 1) All vertices distinct
    {
        vector<pair<long long,long long>> pts;
        pts.reserve(N);
        for (auto &p : v) pts.push_back({p.x, p.y});
        sort(pts.begin(), pts.end());
        for (int i = 1; i < N; ++i) {
            ensuref(!(pts[i] == pts[i-1]),
                    "Duplicate vertex coordinates at positions with value (%lld,%lld)",
                    pts[i].first, pts[i].second);
        }
    }

    // 2) Non-zero area
    long double A = areaPolygon(v);
    ensuref(A > 0, "Polygon area must be positive");

    // 3) No three consecutive points collinear
    for (int i = 0; i < N; ++i) {
        int j = (i + 1) % N;
        int k = (i + 2) % N;
        long double cr = cross(v[i], v[j], v[k]);
        ensuref(cr != 0.0L,
                "Three consecutive vertices are collinear at indices %d, %d, %d",
                i + 1, j + 1, k + 1);
    }

    // 4) Convexity and consistent CCW orientation
    // For convex polygon given CCW, sign of cross of all consecutive triples is positive
    int signDir = 0;
    for (int i = 0; i < N; ++i) {
        int j = (i + 1) % N;
        int k = (i + 2) % N;
        long double cr = cross(v[i], v[j], v[k]);
        if (cr > 0) {
            if (signDir == 0) signDir = 1;
            else ensuref(signDir == 1, "Polygon is not convex or orientation inconsistent");
        } else if (cr < 0) {
            if (signDir == 0) signDir = -1;
            else ensuref(signDir == -1, "Polygon is not convex or orientation inconsistent");
        }
    }
    // Statement says vertices are given CCW.
    ensuref(signDir >= 0, "Polygon orientation must be counter-clockwise");

    inf.readEof();
}
