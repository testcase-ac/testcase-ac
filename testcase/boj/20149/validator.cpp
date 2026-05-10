#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first segment endpoints
    int x1 = inf.readInt(-1000000, 1000000, "x1");
    inf.readSpace();
    int y1 = inf.readInt(-1000000, 1000000, "y1");
    inf.readSpace();
    int x2 = inf.readInt(-1000000, 1000000, "x2");
    inf.readSpace();
    int y2 = inf.readInt(-1000000, 1000000, "y2");
    inf.readEoln();

    // Read second segment endpoints
    int x3 = inf.readInt(-1000000, 1000000, "x3");
    inf.readSpace();
    int y3 = inf.readInt(-1000000, 1000000, "y3");
    inf.readSpace();
    int x4 = inf.readInt(-1000000, 1000000, "x4");
    inf.readSpace();
    int y4 = inf.readInt(-1000000, 1000000, "y4");
    inf.readEoln();

    // Each segment must have positive length (endpoints must differ)
    ensuref(!(x1 == x2 && y1 == y2),
            "First segment is degenerate: endpoints (%d, %d) and (%d, %d) must be distinct",
            x1, y1, x2, y2);
    ensuref(!(x3 == x4 && y3 == y4),
            "Second segment is degenerate: endpoints (%d, %d) and (%d, %d) must be distinct",
            x3, y3, x4, y4);

    inf.readEof();
    return 0;
}
