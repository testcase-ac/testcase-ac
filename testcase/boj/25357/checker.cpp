#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

struct Segment {
    Point a;
    Point b;
};

struct Answer {
    long long length;
};

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

vector<Point> requiredPoints;

bool between(long long value, long long lo, long long hi) {
    if (lo > hi) {
        swap(lo, hi);
    }
    return lo <= value && value <= hi;
}

bool containsPoint(const Segment& s, const Point& p) {
    if (s.a.x == s.b.x) {
        return p.x == s.a.x && between(p.y, s.a.y, s.b.y);
    }
    return p.y == s.a.y && between(p.x, s.a.x, s.b.x);
}

bool intersects(const Segment& lhs, const Segment& rhs) {
    bool lhsVertical = lhs.a.x == lhs.b.x;
    bool rhsVertical = rhs.a.x == rhs.b.x;

    if (lhsVertical && rhsVertical) {
        return lhs.a.x == rhs.a.x &&
               max(min(lhs.a.y, lhs.b.y), min(rhs.a.y, rhs.b.y)) <=
                   min(max(lhs.a.y, lhs.b.y), max(rhs.a.y, rhs.b.y));
    }
    if (!lhsVertical && !rhsVertical) {
        return lhs.a.y == rhs.a.y &&
               max(min(lhs.a.x, lhs.b.x), min(rhs.a.x, rhs.b.x)) <=
                   min(max(lhs.a.x, lhs.b.x), max(rhs.a.x, rhs.b.x));
    }

    const Segment& vertical = lhsVertical ? lhs : rhs;
    const Segment& horizontal = lhsVertical ? rhs : lhs;
    return between(vertical.a.x, horizontal.a.x, horizontal.b.x) &&
           between(horizontal.a.y, vertical.a.y, vertical.b.y);
}

Answer readAnswer(InStream& stream) {
    int n = stream.readInt(0, 100, "number of segments");
    stream.readEoln();

    vector<Segment> segments(n);
    long long totalLength = 0;
    for (int i = 0; i < n; ++i) {
        long long x1 = stream.readLong(-1000000000LL, 1000000000LL,
                                       format("x1[%d]", i + 1).c_str());
        long long y1 = stream.readLong(-1000000000LL, 1000000000LL,
                                       format("y1[%d]", i + 1).c_str());
        long long x2 = stream.readLong(-1000000000LL, 1000000000LL,
                                       format("x2[%d]", i + 1).c_str());
        long long y2 = stream.readLong(-1000000000LL, 1000000000LL,
                                       format("y2[%d]", i + 1).c_str());
        stream.readEoln();

        if (x1 != x2 && y1 != y2) {
            stream.quitf(_wa, "segment %d is neither horizontal nor vertical", i + 1);
        }

        segments[i] = {{x1, y1}, {x2, y2}};
        totalLength += llabs(x1 - x2) + llabs(y1 - y2);
    }
    stream.readEof();

    Dsu dsu(n + 3);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (intersects(segments[i], segments[j])) {
                dsu.unite(i, j);
            }
        }
        for (int j = 0; j < 3; ++j) {
            if (containsPoint(segments[i], requiredPoints[j])) {
                dsu.unite(i, n + j);
            }
        }
    }

    if (dsu.find(n) != dsu.find(n + 1) || dsu.find(n) != dsu.find(n + 2)) {
        stream.quitf(_wa, "the three input points are not connected");
    }

    return {totalLength};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    requiredPoints.resize(3);
    for (int i = 0; i < 3; ++i) {
        requiredPoints[i].x = inf.readLong();
        requiredPoints[i].y = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.length > jury.length) {
        quitf(_wa, "participant length %lld exceeds jury length %lld",
              participant.length, jury.length);
    }
    if (participant.length < jury.length) {
        quitf(_fail, "participant length %lld is better than jury length %lld",
              participant.length, jury.length);
    }

    quitf(_ok, "answer length %lld", participant.length);
}
