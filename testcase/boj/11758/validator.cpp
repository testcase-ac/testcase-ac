#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read P1
    int x1 = inf.readInt(-10000, 10000, "x1");
    inf.readSpace();
    int y1 = inf.readInt(-10000, 10000, "y1");
    inf.readEoln();

    // Read P2
    int x2 = inf.readInt(-10000, 10000, "x2");
    inf.readSpace();
    int y2 = inf.readInt(-10000, 10000, "y2");
    inf.readEoln();

    // Read P3
    int x3 = inf.readInt(-10000, 10000, "x3");
    inf.readSpace();
    int y3 = inf.readInt(-10000, 10000, "y3");
    inf.readEoln();

    // Check that all three points are pairwise distinct
    ensuref(!(x1 == x2 && y1 == y2),
            "Points P1 and P2 coincide: P1=(%d,%d), P2=(%d,%d)", x1, y1, x2, y2);
    ensuref(!(x2 == x3 && y2 == y3),
            "Points P2 and P3 coincide: P2=(%d,%d), P3=(%d,%d)", x2, y2, x3, y3);
    ensuref(!(x1 == x3 && y1 == y3),
            "Points P1 and P3 coincide: P1=(%d,%d), P3=(%d,%d)", x1, y1, x3, y3);

    inf.readEof();
    return 0;
}
