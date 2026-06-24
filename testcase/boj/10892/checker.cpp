#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

struct Triangle {
    int v[3];
};

int n;
vector<Point> points;

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool between(long long a, long long b, long long c) {
    return min(a, b) <= c && c <= max(a, b);
}

bool onSegment(const Point& a, const Point& b, const Point& p) {
    return cross(a, b, p) == 0 && between(a.x, b.x, p.x) && between(a.y, b.y, p.y);
}

bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    long long ab_c = cross(a, b, c);
    long long ab_d = cross(a, b, d);
    long long cd_a = cross(c, d, a);
    long long cd_b = cross(c, d, b);

    if (ab_c == 0 && onSegment(a, b, c)) return true;
    if (ab_d == 0 && onSegment(a, b, d)) return true;
    if (cd_a == 0 && onSegment(c, d, a)) return true;
    if (cd_b == 0 && onSegment(c, d, b)) return true;

    return (ab_c < 0) != (ab_d < 0) && (cd_a < 0) != (cd_b < 0);
}

bool pointInOrOnTriangle(const Point& p, const Triangle& tri) {
    long long signs[3];
    for (int i = 0; i < 3; ++i) {
        const Point& a = points[tri.v[i]];
        const Point& b = points[tri.v[(i + 1) % 3]];
        signs[i] = cross(a, b, p);
    }

    bool hasPositive = false;
    bool hasNegative = false;
    for (long long sign : signs) {
        hasPositive = hasPositive || sign > 0;
        hasNegative = hasNegative || sign < 0;
    }
    return !(hasPositive && hasNegative);
}

bool trianglesOverlap(const Triangle& a, const Triangle& b) {
    for (int i = 0; i < 3; ++i) {
        const Point& a1 = points[a.v[i]];
        const Point& a2 = points[a.v[(i + 1) % 3]];
        for (int j = 0; j < 3; ++j) {
            const Point& b1 = points[b.v[j]];
            const Point& b2 = points[b.v[(j + 1) % 3]];
            if (segmentsIntersect(a1, a2, b1, b2)) {
                return true;
            }
        }
    }

    return pointInOrOnTriangle(points[a.v[0]], b) || pointInOrOnTriangle(points[b.v[0]], a);
}

vector<Triangle> readAnswer(InStream& stream) {
    vector<Triangle> triangles(n);
    vector<int> used(3 * n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            int index = stream.readInt(1, 3 * n, format("triangle[%d][%d]", i + 1, j + 1).c_str());
            --index;
            if (used[index]) {
                stream.quitf(_wa, "stake %d is used more than once", index + 1);
            }
            used[index] = 1;
            triangles[i].v[j] = index;
        }
        stream.readEoln();
    }

    stream.readEof();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (trianglesOverlap(triangles[i], triangles[j])) {
                stream.quitf(_wa, "triangles %d and %d overlap", i + 1, j + 1);
            }
        }
    }

    return triangles;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    points.resize(3 * n);
    for (int i = 0; i < 3 * n; ++i) {
        points[i].x = inf.readLong();
        points[i].y = inf.readLong();
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid non-overlapping triangle division");
}
