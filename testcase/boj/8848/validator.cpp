#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(n, 1000, "M");
    inf.readEoln();

    ensuref(1LL * n * m <= 1000, "N*M must be at most 1000, got %lld",
            1LL * n * m);

    int pieces = n * m;
    for (int i = 1; i <= pieces; ++i) {
        inf.readInt(0, pieces, "neighbor_1");
        inf.readSpace();
        inf.readInt(0, pieces, "neighbor_2");
        inf.readSpace();
        inf.readInt(0, pieces, "neighbor_3");
        inf.readSpace();
        inf.readInt(0, pieces, "neighbor_4");
        inf.readEoln();
    }

    int a = inf.readInt(1, pieces, "A");
    inf.readSpace();
    int b = inf.readInt(1, pieces, "B");
    inf.readEoln();

    ensuref(a != b, "the first two pieces must be distinct, got %d twice", a);

    inf.readEof();
    return 0;
}
