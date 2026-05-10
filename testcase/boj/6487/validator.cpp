#include "testlib.h"
#include <cmath>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

long long cross3(const Point &a, const Point &b, const Point &c) {
    // cross(b-a, c-a)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        Point p[4];
        for (int i = 0; i < 4; ++i) {
            p[i].x = inf.readInt(-1000, 1000, ("x" + to_string(i + 1)).c_str());
            inf.readSpace();
            p[i].y = inf.readInt(-1000, 1000, ("y" + to_string(i + 1)).c_str());
            if (i != 3) inf.readSpace();
        }
        inf.readEoln();

        // Check distinct points within each line
        ensuref(!(p[0].x == p[1].x && p[0].y == p[1].y),
                "First line endpoints must be distinct");
        ensuref(!(p[2].x == p[3].x && p[2].y == p[3].y),
                "Second line endpoints must be distinct");

        // Now enforce the problem's global guarantee by computing intersection type.

        Point A = p[0], B = p[1], C = p[2], D = p[3];
        Point v1{B.x - A.x, B.y - A.y};
        Point v2{D.x - C.x, D.y - C.y};

        long long cross_v = cross(v1, v2);

        if (cross_v == 0) {
            // Parallel or coincident
            long long c1 = cross3(A, B, C);
            if (c1 == 0) {
                // Coincident lines: infinite intersections
                // Expected output type: LINE
                // Just ensure this situation actually exists; nothing else to check.
            } else {
                // Parallel and distinct: no intersection
                // Expected output type: NONE.
            }
        } else {
            // Unique intersection point exists for infinite lines.
            // Nothing more to validate, since coordinates are bounded and well-defined.
            // (No division-by-zero etc. in the mathematical definition.)
        }
    }

    inf.readEof();
}
