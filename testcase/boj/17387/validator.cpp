#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: x1 y1 x2 y2
    int x1 = inf.readInt(-1000000, 1000000, "x1");
    inf.readSpace();
    int y1 = inf.readInt(-1000000, 1000000, "y1");
    inf.readSpace();
    int x2 = inf.readInt(-1000000, 1000000, "x2");
    inf.readSpace();
    int y2 = inf.readInt(-1000000, 1000000, "y2");
    inf.readEoln();

    // Read second line: x3 y3 x4 y4
    int x3 = inf.readInt(-1000000, 1000000, "x3");
    inf.readSpace();
    int y3 = inf.readInt(-1000000, 1000000, "y3");
    inf.readSpace();
    int x4 = inf.readInt(-1000000, 1000000, "x4");
    inf.readSpace();
    int y4 = inf.readInt(-1000000, 1000000, "y4");
    inf.readEoln();

    // Validate that each segment is non-degenerate (length > 0)
    ensuref(x1 != x2 || y1 != y2,
            "Segment L1 is degenerate: endpoints must differ, got (%d, %d) and (%d, %d)",
            x1, y1, x2, y2);
    ensuref(x3 != x4 || y3 != y4,
            "Segment L2 is degenerate: endpoints must differ, got (%d, %d) and (%d, %d)",
            x3, y3, x4, y4);

    inf.readEof();
    return 0;
}
