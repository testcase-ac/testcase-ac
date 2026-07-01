#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

long long cross(const Point& a, const Point& b, const Point& c) {
    long long ux = b.x - a.x;
    long long uy = b.y - a.y;
    long long vx = c.x - a.x;
    long long vy = c.y - a.y;
    return ux * vy - uy * vx;
}

bool between(long long a, long long b, long long c) {
    return min(a, b) <= c && c <= max(a, b);
}

bool onSegment(const Point& a, const Point& b, const Point& p) {
    return cross(a, b, p) == 0 && between(a.x, b.x, p.x) && between(a.y, b.y, p.y);
}

int sign(long long value) {
    if (value < 0) return -1;
    if (value > 0) return 1;
    return 0;
}

bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    long long abC = cross(a, b, c);
    long long abD = cross(a, b, d);
    long long cdA = cross(c, d, a);
    long long cdB = cross(c, d, b);

    if (sign(abC) * sign(abD) < 0 && sign(cdA) * sign(cdB) < 0) {
        return true;
    }

    return onSegment(a, b, c) || onSegment(a, b, d) ||
           onSegment(c, d, a) || onSegment(c, d, b);
}

bool adjacentEdges(int first, int second, int n) {
    if (first == second) return true;
    return (first + 1) % n == second || (second + 1) % n == first;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "n");
    inf.readEoln();

    vector<Point> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].x = inf.readLong(-100000000LL, 100000000LL, "x_i");
        inf.readSpace();
        p[i].y = inf.readLong(-100000000LL, 100000000LL, "y_i");
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        const Point& a = p[i];
        const Point& b = p[(i + 1) % n];
        const Point& c = p[(i + 2) % n];
        ensuref(cross(a, b, c) != 0,
                "three consecutive vertices are collinear at indices %d, %d, %d",
                i + 1, (i + 1) % n + 1, (i + 2) % n + 1);
    }

    __int128 twiceArea = 0;
    for (int i = 0; i < n; ++i) {
        const Point& a = p[i];
        const Point& b = p[(i + 1) % n];
        twiceArea += (__int128)a.x * b.y - (__int128)a.y * b.x;
    }
    ensuref(twiceArea > 0, "vertices must be given in counter-clockwise order");

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacentEdges(i, j, n)) {
                continue;
            }

            ensuref(!segmentsIntersect(p[i], p[(i + 1) % n], p[j], p[(j + 1) % n]),
                    "polygon edges %d-%d and %d-%d intersect or touch",
                    i + 1, (i + 1) % n + 1, j + 1, (j + 1) % n + 1);
        }
    }

    // CHECK: The statement guarantees an answer exists; this validator checks
    // the polygon contract but does not solve the tangent-existence condition.
    inf.readEof();
}
