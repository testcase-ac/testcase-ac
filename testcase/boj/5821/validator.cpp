#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 100000, "R");
    inf.readSpace();
    int l = inf.readInt(1, 1000000000, "L");
    inf.readSpace();
    long long b = inf.readLong(0LL, 2000000000000000LL, "B");
    inf.readEoln();

    int previous = 1;
    for (int i = 0; i < r; ++i) {
        int x = inf.readInt(1, l, "X_i");
        inf.readEoln();
        ensuref(i == 0 || previous <= x,
                "coordinates must be nondecreasing: X[%d]=%d, X[%d]=%d",
                i - 1, previous, i, x);
        previous = x;
    }

    inf.readEof();
    return 0;
}
