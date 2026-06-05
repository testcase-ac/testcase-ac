#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    int a1 = inf.readInt(1, n, "A_1");
    inf.readSpace();
    int a2 = inf.readInt(1, n, "A_2");
    inf.readEoln();
    ensuref(a1 < a2, "A_1 must be less than A_2: %d >= %d", a1, a2);

    int b1 = inf.readInt(1, n, "B_1");
    inf.readSpace();
    int b2 = inf.readInt(1, n, "B_2");
    inf.readEoln();
    ensuref(b1 < b2, "B_1 must be less than B_2: %d >= %d", b1, b2);

    inf.readEof();
}
