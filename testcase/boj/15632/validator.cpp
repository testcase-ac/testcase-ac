#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 0; i < 3; ++i) {
        int x = inf.readInt(1, 99, "x");
        inf.readSpace();
        int y = inf.readInt(1, 99, "y");
        inf.readSpace();
        int r = inf.readInt(1, 50, "r");
        inf.readEoln();

        ensuref(r <= x && x <= 100 - r,
                "circle %d is not fully inside square horizontally: x=%d r=%d",
                i + 1,
                x,
                r);
        ensuref(r <= y && y <= 100 - r,
                "circle %d is not fully inside square vertically: y=%d r=%d",
                i + 1,
                y,
                r);
    }

    inf.readEof();
}
