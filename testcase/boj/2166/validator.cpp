#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long cross(pair<long long, long long> a, pair<long long, long long> b,
                pair<long long, long long> c) {
    long long x1 = b.first - a.first;
    long long y1 = b.second - a.second;
    long long x2 = c.first - a.first;
    long long y2 = c.second - a.second;
    return x1 * y2 - y1 * x2;
}

bool between(long long a, long long b, long long x) {
    return min(a, b) <= x && x <= max(a, b);
}

bool segmentsIntersect(pair<long long, long long> a, pair<long long, long long> b,
                       pair<long long, long long> c, pair<long long, long long> d) {
    long long abC = cross(a, b, c);
    long long abD = cross(a, b, d);
    long long cdA = cross(c, d, a);
    long long cdB = cross(c, d, b);

    if (abC == 0 && between(a.first, b.first, c.first) &&
        between(a.second, b.second, c.second)) {
        return true;
    }
    if (abD == 0 && between(a.first, b.first, d.first) &&
        between(a.second, b.second, d.second)) {
        return true;
    }
    if (cdA == 0 && between(c.first, d.first, a.first) &&
        between(c.second, d.second, a.second)) {
        return true;
    }
    if (cdB == 0 && between(c.first, d.first, b.first) &&
        between(c.second, d.second, b.second)) {
        return true;
    }
    return (abC > 0) != (abD > 0) && (cdA > 0) != (cdB > 0);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 10000, "N");
    inf.readEoln();

    vector<pair<long long, long long>> points;
    points.reserve(n);
    set<pair<long long, long long>> seen;

    for (int i = 0; i < n; i++) {
        int x = inf.readInt(-100000, 100000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-100000, 100000, "y_i");
        inf.readEoln();
        ensuref(seen.insert({x, y}).second,
                "duplicate point at index %d: %d %d", i + 1, x, y);
        points.push_back({x, y});
    }

    long long twiceArea = 0;
    for (int i = 0; i < n; i++) {
        const auto [x1, y1] = points[i];
        const auto [x2, y2] = points[(i + 1) % n];
        twiceArea += x1 * y2 - x2 * y1;
    }
    ensuref(twiceArea != 0, "polygon area must be nonzero");

    for (int i = 0; i < n; i++) {
        int nextI = (i + 1) % n;
        for (int j = i + 1; j < n; j++) {
            int nextJ = (j + 1) % n;
            if (i == nextJ || nextI == j) {
                continue;
            }
            ensuref(!segmentsIntersect(points[i], points[nextI], points[j], points[nextJ]),
                    "non-adjacent edges %d-%d and %d-%d intersect",
                    i + 1, nextI + 1, j + 1, nextJ + 1);
        }
    }

    inf.readEof();
    return 0;
}
