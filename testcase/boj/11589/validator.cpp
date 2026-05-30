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

long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool between(long long a, long long b, long long x) {
    return min(a, b) <= x && x <= max(a, b);
}

bool onSegment(Point a, Point b, Point p) {
    return cross(a, b, p) == 0 && between(a.x, b.x, p.x) && between(a.y, b.y, p.y);
}

int sign(long long value) {
    if (value < 0) return -1;
    if (value > 0) return 1;
    return 0;
}

bool segmentsTouch(Segment s, Segment t) {
    long long c1 = cross(s.a, s.b, t.a);
    long long c2 = cross(s.a, s.b, t.b);
    long long c3 = cross(t.a, t.b, s.a);
    long long c4 = cross(t.a, t.b, s.b);

    if (onSegment(s.a, s.b, t.a) || onSegment(s.a, s.b, t.b) ||
        onSegment(t.a, t.b, s.a) || onSegment(t.a, t.b, s.b)) {
        return true;
    }

    return sign(c1) != sign(c2) && sign(c3) != sign(c4);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 5000, "N");
    inf.readEoln();

    vector<Segment> sticks;
    sticks.reserve(N);

    for (int i = 0; i < N; i++) {
        int x1 = inf.readInt(0, 10000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, 10000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(0, 10000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, 10000, "y2");
        inf.readEoln();

        Segment current{{x1, y1}, {x2, y2}};
        ensuref(!(current.a.x == current.b.x && current.a.y == current.b.y),
                "stick %d has equal endpoints", i + 1);

        for (int j = 0; j < (int)sticks.size(); ++j) {
            ensuref(!segmentsTouch(current, sticks[j]),
                    "sticks %d and %d touch or intersect", j + 1, i + 1);
        }
        sticks.push_back(current);
    }

    inf.readEof();
    return 0;
}
