#include "testlib.h"
#include <cmath>
using namespace std;

// Helper function to check if two points are the same
bool same_point(int x1, int y1, int x2, int y2) {
    return x1 == x2 && y1 == y2;
}

// Helper function to check if three points are collinear
bool collinear(int x1, int y1, int x2, int y2, int x3, int y3) {
    // Area of triangle == 0
    // (x2-x1)*(y3-y1) == (y2-y1)*(x3-x1)
    long long dx1 = x2 - x1, dy1 = y2 - y1;
    long long dx2 = x3 - x1, dy2 = y3 - y1;
    return dx1 * dy2 == dy1 * dx2;
}

// Helper function to check if a segment has nonzero length
bool nonzero_length(int x1, int y1, int x2, int y2) {
    return !(x1 == x2 && y1 == y2);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MINC = -1000000, MAXC = 1000000;

    // Read first line: x1 y1 x2 y2
    int x1 = inf.readInt(MINC, MAXC, "x1");
    inf.readSpace();
    int y1 = inf.readInt(MINC, MAXC, "y1");
    inf.readSpace();
    int x2 = inf.readInt(MINC, MAXC, "x2");
    inf.readSpace();
    int y2 = inf.readInt(MINC, MAXC, "y2");
    inf.readEoln();

    // Read second line: x3 y3 x4 y4
    int x3 = inf.readInt(MINC, MAXC, "x3");
    inf.readSpace();
    int y3 = inf.readInt(MINC, MAXC, "y3");
    inf.readSpace();
    int x4 = inf.readInt(MINC, MAXC, "x4");
    inf.readSpace();
    int y4 = inf.readInt(MINC, MAXC, "y4");
    inf.readEoln();

    // Check that both segments have nonzero length
    ensuref(nonzero_length(x1, y1, x2, y2), "L1 has zero length: (%d,%d)-(%d,%d)", x1, y1, x2, y2);
    ensuref(nonzero_length(x3, y3, x4, y4), "L2 has zero length: (%d,%d)-(%d,%d)", x3, y3, x4, y4);

    // Check that no three points are collinear
    // (x1,y1)-(x2,y2)-(x3,y3)
    ensuref(!collinear(x1, y1, x2, y2, x3, y3),
        "Points (%d,%d), (%d,%d), (%d,%d) are collinear", x1, y1, x2, y2, x3, y3);
    // (x1,y1)-(x2,y2)-(x4,y4)
    ensuref(!collinear(x1, y1, x2, y2, x4, y4),
        "Points (%d,%d), (%d,%d), (%d,%d) are collinear", x1, y1, x2, y2, x4, y4);
    // (x1,y1)-(x3,y3)-(x4,y4)
    ensuref(!collinear(x1, y1, x3, y3, x4, y4),
        "Points (%d,%d), (%d,%d), (%d,%d) are collinear", x1, y1, x3, y3, x4, y4);
    // (x2,y2)-(x3,y3)-(x4,y4)
    ensuref(!collinear(x2, y2, x3, y3, x4, y4),
        "Points (%d,%d), (%d,%d), (%d,%d) are collinear", x2, y2, x3, y3, x4, y4);

    inf.readEof();
}
