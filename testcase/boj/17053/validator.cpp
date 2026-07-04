#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>
using namespace std;

struct Segment {
    int x1;
    int y1;
    int x2;
    int y2;
};

static bool isEndpoint(const Segment& s, int x, int y) {
    return (s.x1 == x && s.y1 == y) || (s.x2 == x && s.y2 == y);
}

static bool containsPoint(const Segment& s, int x, int y) {
    if (s.x1 == s.x2) {
        return x == s.x1 && min(s.y1, s.y2) <= y && y <= max(s.y1, s.y2);
    }
    return y == s.y1 && min(s.x1, s.x2) <= x && x <= max(s.x1, s.x2);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<Segment> segments;
    segments.reserve(n);

    array<array<vector<int>, 301>, 301> pointSegments;
    array<array<bool, 301>, 300> horizontalUnit{};
    array<array<bool, 300>, 301> verticalUnit{};

    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(0, 300, "A_i");
        inf.readSpace();
        int b = inf.readInt(0, 300, "B_i");
        inf.readSpace();
        int c = inf.readInt(0, 300, "C_i");
        inf.readSpace();
        int d = inf.readInt(0, 300, "D_i");
        inf.readEoln();

        ensuref(a != c || b != d, "segment %d is degenerate", i + 1);
        ensuref(a == c || b == d, "segment %d is not axis-aligned", i + 1);

        Segment current{a, b, c, d};
        if (b == d) {
            int lx = min(a, c);
            int rx = max(a, c);
            for (int x = lx; x < rx; ++x) {
                ensuref(!horizontalUnit[x][b],
                        "segment %d overlaps another horizontal segment near (%d, %d)",
                        i + 1, x, b);
                horizontalUnit[x][b] = true;
            }
        } else {
            int ly = min(b, d);
            int ry = max(b, d);
            for (int y = ly; y < ry; ++y) {
                ensuref(!verticalUnit[a][y],
                        "segment %d overlaps another vertical segment near (%d, %d)",
                        i + 1, a, y);
                verticalUnit[a][y] = true;
            }
        }

        int lx = min(a, c);
        int rx = max(a, c);
        int ly = min(b, d);
        int ry = max(b, d);
        for (int x = lx; x <= rx; ++x) {
            for (int y = ly; y <= ry; ++y) {
                for (int previous : pointSegments[x][y]) {
                    ensuref(isEndpoint(current, x, y) &&
                                    isEndpoint(segments[previous], x, y),
                            "segment %d intersects segment %d at (%d, %d) without a common endpoint",
                            i + 1, previous + 1, x, y);
                }
                pointSegments[x][y].push_back(i);
            }
        }

        segments.push_back(current);
    }

    int x = inf.readInt(0, 300, "X");
    inf.readSpace();
    int y = inf.readInt(0, 300, "Y");
    inf.readEoln();
    inf.readEof();

    bool targetOnSegment = false;
    for (const Segment& segment : segments) {
        if (containsPoint(segment, x, y)) {
            targetOnSegment = true;
            break;
        }
    }
    ensuref(targetOnSegment, "target point (%d, %d) is not on any segment", x, y);
}
