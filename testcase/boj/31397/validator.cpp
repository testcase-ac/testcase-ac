#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct P {
    long long x, y;
};

bool operator<(const P &a, const P &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool operator==(const P &a, const P &b) {
    return a.x == b.x && a.y == b.y;
}

__int128 cross(const P &a, const P &b, const P &c) {
    return (__int128)(b.x - a.x) * (c.y - a.y) -
           (__int128)(b.y - a.y) * (c.x - a.x);
}

__int128 signedDoubleArea(const vector<P> &p) {
    __int128 s = 0;
    int n = (int)p.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        s += (__int128)p[i].x * p[j].y - (__int128)p[i].y * p[j].x;
    }
    return s;
}

vector<P> convexHull(vector<P> pts) {
    sort(pts.begin(), pts.end());

    vector<P> lower, upper;
    for (const P &p : pts) {
        while (lower.size() >= 2 &&
               cross(lower[lower.size() - 2], lower.back(), p) <= 0) {
            lower.pop_back();
        }
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        const P &p = pts[i];
        while (upper.size() >= 2 &&
               cross(upper[upper.size() - 2], upper.back(), p) <= 0) {
            upper.pop_back();
        }
        upper.push_back(p);
    }

    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
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

    {
        vector<P> pts = v;
        sort(pts.begin(), pts.end());
        for (int i = 1; i < N; ++i) {
            ensuref(!(pts[i] == pts[i - 1]),
                    "Duplicate vertex coordinates at positions with value (%lld,%lld)",
                    pts[i].x, pts[i].y);
        }
    }

    ensuref(signedDoubleArea(v) > 0, "Polygon orientation must be counter-clockwise");

    vector<P> hull = convexHull(v);
    ensuref((int)hull.size() == N,
            "All vertices must be extreme points with no three collinear");

    int start = -1;
    for (int i = 0; i < N; ++i) {
        if (v[i] == hull[0]) {
            start = i;
            break;
        }
    }
    ensuref(start != -1, "Internal error while matching hull vertices");
    for (int i = 0; i < N; ++i) {
        ensuref(v[(start + i) % N] == hull[i],
                "Vertices must be listed in counter-clockwise convex boundary order");
    }

    inf.readEof();
}
