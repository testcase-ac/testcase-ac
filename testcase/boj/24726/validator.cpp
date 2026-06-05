#include "testlib.h"

long long cross(long long ax, long long ay,
                long long bx, long long by,
                long long cx, long long cy) {
    return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x1 = inf.readInt(0, 10000, "x1");
    inf.readSpace();
    int y1 = inf.readInt(0, 10000, "y1");
    inf.readSpace();
    int x2 = inf.readInt(0, 10000, "x2");
    inf.readSpace();
    int y2 = inf.readInt(0, 10000, "y2");
    inf.readSpace();
    int x3 = inf.readInt(0, 10000, "x3");
    inf.readSpace();
    int y3 = inf.readInt(0, 10000, "y3");
    inf.readEoln();

    ensuref(cross(x1, y1, x2, y2, x3, y3) != 0,
            "the three points must not be collinear");

    inf.readEof();
}
