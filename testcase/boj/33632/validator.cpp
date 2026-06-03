#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int W = inf.readInt(1, 30, "W");
    inf.readSpace();
    int H = inf.readInt(1, 30, "H");
    inf.readEoln();

    int x = inf.readInt(0, W, "x");
    inf.readSpace();
    int y = inf.readInt(0, H, "y");
    inf.readEoln();

    int x1 = inf.readInt(0, W, "x1");
    inf.readSpace();
    int y1 = inf.readInt(0, H, "y1");
    inf.readSpace();
    int x2 = inf.readInt(0, W, "x2");
    inf.readSpace();
    int y2 = inf.readInt(0, H, "y2");
    inf.readEoln();

    ensuref(x1 < x2, "goal endpoints must satisfy x1 < x2: x1=%d, x2=%d", x1, x2);
    ensuref(y1 == y2, "goal endpoints must have equal y: y1=%d, y2=%d", y1, y2);
    ensuref(y != y1, "ball y must differ from goal y: y=%d, y1=%d", y, y1);

    inf.readEof();
}
