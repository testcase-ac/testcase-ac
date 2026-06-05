#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(-10000, 10000, "A");
    inf.readSpace();
    int b = inf.readInt(-10000, 10000, "B");
    inf.readSpace();
    inf.readInt(-100000, 100000, "C");
    inf.readEoln();

    ensuref(a != 0 || b != 0, "A and B must not both be zero");

    int x1 = inf.readInt(-100000, 100000, "X_1");
    inf.readSpace();
    int x2 = inf.readInt(-100000, 100000, "X_2");
    inf.readSpace();
    int y1 = inf.readInt(-100000, 100000, "Y_1");
    inf.readSpace();
    int y2 = inf.readInt(-100000, 100000, "Y_2");
    inf.readEoln();

    ensuref(x1 < x2, "X_1 must be less than X_2: %d >= %d", x1, x2);
    ensuref(y1 < y2, "Y_1 must be less than Y_2: %d >= %d", y1, y2);

    inf.readEof();
}
