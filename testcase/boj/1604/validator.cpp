#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
};

struct Segment {
    Point a;
    Point b;
};

struct Line {
    long long a;
    long long b;
    long long c;
};

bool outsideSquare(const Point& p) {
    return p.x < -10 || p.x > 10 || p.y < -10 || p.y > 10;
}

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Line lineOf(const Segment& s) {
    long long a = s.b.y - s.a.y;
    long long b = s.a.x - s.b.x;
    long long c = a * s.a.x + b * s.a.y;
    return {a, b, c};
}

bool sameLine(const Segment& x, const Segment& y) {
    return cross(x.a, x.b, y.a) == 0 && cross(x.a, x.b, y.b) == 0;
}

bool betweenRational(long long valueNumerator, long long denominator, long long lo, long long hi) {
    if (denominator < 0) {
        valueNumerator = -valueNumerator;
        denominator = -denominator;
    }
    return lo * denominator <= valueNumerator && valueNumerator <= hi * denominator;
}

bool rationalPointOnSegment(long long xNumerator, long long yNumerator, long long denominator,
                            const Segment& s) {
    long long minX = min(s.a.x, s.b.x);
    long long maxX = max(s.a.x, s.b.x);
    long long minY = min(s.a.y, s.b.y);
    long long maxY = max(s.a.y, s.b.y);
    return betweenRational(xNumerator, denominator, minX, maxX) &&
           betweenRational(yNumerator, denominator, minY, maxY);
}

bool threeSegmentsMeetAtOnePoint(const Segment& x, const Segment& y, const Segment& z) {
    Line lx = lineOf(x);
    Line ly = lineOf(y);
    Line lz = lineOf(z);

    long long denominator = lx.a * ly.b - ly.a * lx.b;
    if (denominator == 0) {
        return false;
    }

    long long xNumerator = ly.b * lx.c - lx.b * ly.c;
    long long yNumerator = lx.a * ly.c - ly.a * lx.c;

    return lz.a * xNumerator + lz.b * yNumerator == lz.c * denominator &&
           rationalPointOnSegment(xNumerator, yNumerator, denominator, x) &&
           rationalPointOnSegment(xNumerator, yNumerator, denominator, y) &&
           rationalPointOnSegment(xNumerator, yNumerator, denominator, z);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    vector<Segment> segments;
    segments.reserve(n);
    for (int i = 0; i < n; ++i) {
        Point p1;
        Point p2;
        p1.x = inf.readInt(-1000, 1000, "x1");
        inf.readSpace();
        p1.y = inf.readInt(-1000, 1000, "y1");
        inf.readSpace();
        p2.x = inf.readInt(-1000, 1000, "x2");
        inf.readSpace();
        p2.y = inf.readInt(-1000, 1000, "y2");
        inf.readEoln();

        ensuref(outsideSquare(p1), "segment %d first endpoint is not outside the square", i + 1);
        ensuref(outsideSquare(p2), "segment %d second endpoint is not outside the square", i + 1);
        ensuref(p1.x != p2.x || p1.y != p2.y, "segment %d has identical endpoints", i + 1);

        segments.push_back({p1, p2});
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(!sameLine(segments[i], segments[j]),
                    "segments %d and %d lie on the same line", i + 1, j + 1);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                ensuref(!threeSegmentsMeetAtOnePoint(segments[i], segments[j], segments[k]),
                        "segments %d, %d, and %d meet at one point", i + 1, j + 1, k + 1);
            }
        }
    }

    inf.readEof();
}
