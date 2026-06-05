#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 12, "n");
    inf.readSpace();
    int x = inf.readInt(1, 2 * n, "x");
    inf.readSpace();
    int y = inf.readInt(1, 2 * n, "y");
    inf.readEoln();

    ensuref(x < y, "expected x < y, got x=%d y=%d", x, y);
    int gap = y - x - 1;
    ensuref(1 <= gap && gap <= n,
            "expected 1 <= y - x - 1 <= n, got n=%d x=%d y=%d gap=%d",
            n,
            x,
            y,
            gap);

    inf.readEof();
}
