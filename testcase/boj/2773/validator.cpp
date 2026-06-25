#include "testlib.h"
#include <array>
#include <cmath>
using namespace std;

struct Point {
    double x;
    double y;
};

double distanceFromLine(Point p, Point a, Point b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double cross = dx * (p.y - a.y) - dy * (p.x - a.x);
    return fabs(cross) / hypot(dx, dy);
}

bool samePoint(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no bounds for dataset count or coordinates.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        array<Point, 3> p;
        for (int i = 0; i < 3; ++i) {
            p[i].x = inf.readDouble(-1e9, 1e9, "x");
            inf.readSpace();
            p[i].y = inf.readDouble(-1e9, 1e9, "y");
            inf.readEoln();
        }

        ensuref(!samePoint(p[0], p[1]), "A and B must be distinct");
        ensuref(!samePoint(p[1], p[2]), "B and C must be distinct");
        ensuref(!samePoint(p[2], p[0]), "C and A must be distinct");

        ensuref(distanceFromLine(p[0], p[1], p[2]) >= 1.0,
                "A must not be within one unit of line BC");
        ensuref(distanceFromLine(p[1], p[2], p[0]) >= 1.0,
                "B must not be within one unit of line CA");
        ensuref(distanceFromLine(p[2], p[0], p[1]) >= 1.0,
                "C must not be within one unit of line AB");
    }

    inf.readEof();
}
