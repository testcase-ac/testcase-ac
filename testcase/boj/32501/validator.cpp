#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x1 = inf.readInt(-100, 100, "x1");
    inf.readSpace();
    int y1 = inf.readInt(-100, 100, "y1");
    inf.readSpace();
    int x2 = inf.readInt(-100, 100, "x2");
    inf.readSpace();
    int y2 = inf.readInt(-100, 100, "y2");
    inf.readSpace();
    int a = inf.readInt(0, 1000, "a"); // lower bound checked below
    inf.readEoln();

    int dx = x2 - x1;
    int dy = y2 - y1;
    ensuref(1LL * a * a >= 1LL * dx * dx + 1LL * dy * dy,
            "major axis length %d is less than distance between foci", a);

    inf.readEof();
}
