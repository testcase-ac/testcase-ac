#include "testlib.h"

#include <array>

using namespace std;

struct Point {
    long long x;
    long long y;
};

long long cross(const Point& a, const Point& b, const Point& c) {
    long long ux = b.x - a.x;
    long long uy = b.y - a.y;
    long long vx = c.x - b.x;
    long long vy = c.y - b.y;
    return ux * vy - uy * vx;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    array<Point, 4> p;
    for (int i = 0; i < 4; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        p[i].x = inf.readInt(-10000, 10000, "x");
        inf.readSpace();
        p[i].y = inf.readInt(-10000, 10000, "y");
    }
    inf.readEoln();

    long long first = cross(p[0], p[1], p[2]);
    ensuref(first != 0, "vertices 1, 2, and 3 are collinear");
    for (int i = 1; i < 4; ++i) {
        long long turn = cross(p[i], p[(i + 1) % 4], p[(i + 2) % 4]);
        ensuref(turn != 0, "angle at vertex %d is 180 degrees", (i + 1) % 4 + 1);
        ensuref((turn > 0) == (first > 0),
                "quadrilateral is not strictly convex in vertex order at vertex %d",
                (i + 1) % 4 + 1);
    }

    // CHECK: The Korean BOJ statement gives one quadrilateral; the embedded
    // English original describes multiple terminated cases.
    inf.readEof();
}
