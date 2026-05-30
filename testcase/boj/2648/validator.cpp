#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int x1;
    int y1;
    int x2;
    int y2;
};

int lo(int a, int b) {
    return min(a, b);
}

int hi(int a, int b) {
    return max(a, b);
}

bool vertical(const Segment& s) {
    return s.x1 == s.x2;
}

bool horizontal(const Segment& s) {
    return s.y1 == s.y2;
}

bool rangesIntersect(int a1, int a2, int b1, int b2) {
    return max(lo(a1, a2), lo(b1, b2)) <= min(hi(a1, a2), hi(b1, b2));
}

bool sameOrientationMeet(const Segment& a, const Segment& b) {
    if (horizontal(a) && horizontal(b) && a.y1 == b.y1) {
        return rangesIntersect(a.x1, a.x2, b.x1, b.x2);
    }
    if (vertical(a) && vertical(b) && a.x1 == b.x1) {
        return rangesIntersect(a.y1, a.y2, b.y1, b.y2);
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x0 = inf.readInt(1, 100, "x0");
    inf.readSpace();
    int y0 = inf.readInt(1, 100, "y0");
    inf.readEoln();

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    vector<Segment> segments;
    int x = x0;
    int y = y0;
    for (int i = 0; i < n; ++i) {
        string dir = inf.readToken("[UDRL]", "dir");
        inf.readSpace();
        int distance = inf.readInt(1, 100, "distance");
        inf.readEoln();

        int nx = x;
        int ny = y;
        if (dir[0] == 'U') {
            ny += distance;
        } else if (dir[0] == 'D') {
            ny -= distance;
        } else if (dir[0] == 'R') {
            nx += distance;
        } else {
            nx -= distance;
        }

        ensuref(1 <= nx && nx <= 100 && 1 <= ny && ny <= 100,
                "move %d ends outside coordinate bounds: (%d, %d)", i + 1, nx, ny);
        segments.push_back({x, y, nx, ny});
        x = nx;
        y = ny;
    }

    ensuref(x == x0 && y == y0,
            "path must return to start: ended at (%d, %d), started at (%d, %d)",
            x, y, x0, y0);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(!sameOrientationMeet(segments[i], segments[j]),
                    "same-orientation segments %d and %d meet or overlap", i + 1, j + 1);
        }
    }

    inf.readEof();
}
