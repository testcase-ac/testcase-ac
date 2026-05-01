#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    bool operator<(const Point &o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    bool operator==(const Point &o) const {
        return x == o.x && y == o.y;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of segments
    int N = inf.readInt(1, 60, "N");
    inf.readEoln();

    vector<Point> A(N), B(N);

    for (int i = 0; i < N; ++i) {
        long long x1 = inf.readInt(0, 10000, "x1");
        inf.readSpace();
        long long y1 = inf.readInt(0, 10000, "y1");
        inf.readSpace();
        long long x2 = inf.readInt(0, 10000, "x2");
        inf.readSpace();
        long long y2 = inf.readInt(0, 10000, "y2");
        inf.readEoln();

        // Ensure segment is not degenerate (zero length)
        ensuref(!(x1 == x2 && y1 == y2),
                "Segment %d is degenerate (both endpoints equal: (%lld,%lld))",
                i + 1, x1, y1);

        A[i] = {x1, y1};
        B[i] = {x2, y2};
    }

    // No additional global geometric constraints are stated in the problem.
    // Intersections, overlaps, and arbitrary graph structures are allowed,
    // since polygons can be formed in many ways and the statement does not
    // restrict how segments may intersect.

    inf.readEof();
}
