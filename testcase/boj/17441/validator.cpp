#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(const Point &a, const Point &b, const Point &c) {
    // (b - a) x (c - a)
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    return x1 * y2 - x2 * y1;
}

int sgn(long long v) {
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

// check if two segments (p1,p2) and (q1,q2) properly intersect or touch
bool segmentsIntersect(const Point &p1, const Point &p2,
                       const Point &q1, const Point &q2) {
    long long c1 = cross(p1, p2, q1);
    long long c2 = cross(p1, p2, q2);
    long long c3 = cross(q1, q2, p1);
    long long c4 = cross(q1, q2, p2);

    int s1 = sgn(c1), s2 = sgn(c2), s3 = sgn(c3), s4 = sgn(c4);

    if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0) {
        // Collinear: check 1D overlap on projection
        auto leq = [](long long a, long long b){ return a <= b; };
        auto between = [&](long long a, long long b, long long c){
            // check [min(a,b), max(a,b)] intersects [min(b,c), max(b,c)]
            long long l1 = min(a, b), r1 = max(a, b);
            long long l2 = min(b, c), r2 = max(b, c);
            return !(r1 < l2 || r2 < l1);
        };
        bool overlapX = between(p1.x, p2.x, q1.x) || between(p1.x, p2.x, q2.x) ||
                        between(q1.x, q2.x, p1.x) || between(q1.x, q2.x, p2.x);
        bool overlapY = between(p1.y, p2.y, q1.y) || between(p1.y, p2.y, q2.y) ||
                        between(q1.y, q2.y, p1.y) || between(q1.y, q2.y, p2.y);
        return overlapX && overlapY;
    }

    return (s1 * s2 <= 0) && (s3 * s4 <= 0);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 100000, "N");
    inf.readEoln();

    vector<Point> p(N);
    for (int i = 0; i < N; ++i) {
        p[i].x = inf.readLong(-10000LL, 10000LL, "x_i");
        inf.readSpace();
        p[i].y = inf.readLong(-10000LL, 10000LL, "y_i");
        inf.readEoln();
    }

    // Check consecutive vertices are distinct
    for (int i = 0; i < N; ++i) {
        int j = (i + 1) % N;
        ensuref(!(p[i].x == p[j].x && p[i].y == p[j].y),
                "Consecutive vertices %d and %d must be distinct", i + 1, j + 1);
    }

    // Check orientation is counterclockwise and area > 0
    __int128 area2 = 0;
    for (int i = 0; i < N; ++i) {
        int j = (i + 1) % N;
        area2 += (__int128)p[i].x * p[j].y - (__int128)p[j].x * p[i].y;
    }
    ensuref(area2 > 0,
            "Polygon must be simple with strictly positive area and given CCW; got area2 = %lld",
            (long long)area2);

    // Check simplicity: no non-adjacent edges intersect
    // edges: (i, i+1)
    for (int i = 0; i < N; ++i) {
        int ni = (i + 1) % N;
        for (int j = i + 1; j < N; ++j) {
            int nj = (j + 1) % N;

            // Skip same edge
            if (i == j) continue;
            // Skip adjacent edges sharing a vertex
            if (ni == j || nj == i) continue;
            // Skip first and last edge adjacency
            if (i == 0 && nj == 0 && ni == N - 1) continue;
            if (j == 0 && ni == 0 && nj == N - 1) continue;

            if (segmentsIntersect(p[i], p[ni], p[j], p[nj])) {
                ensuref(false,
                        "Non-adjacent edges (%d,%d) and (%d,%d) intersect",
                        i + 1, ni + 1, j + 1, nj + 1);
            }
        }
    }

    inf.readEof();
}
