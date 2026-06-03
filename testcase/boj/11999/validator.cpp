#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(1, 1000, "X");
    inf.readSpace();
    int y = inf.readInt(1, 1000, "Y");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    ensuref(x < y, "expected X < Y, got X=%d, Y=%d", x, y);
    ensuref(y < m, "expected Y < M, got Y=%d, M=%d", y, m);

    inf.readEof();
}
