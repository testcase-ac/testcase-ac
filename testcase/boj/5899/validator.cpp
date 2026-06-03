#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long x1 = inf.readLong(-100000000LL, 100000000LL, "x1");
        inf.readSpace();
        long long y1 = inf.readLong(-100000000LL, 100000000LL, "y1");
        inf.readSpace();
        long long x2 = inf.readLong(-100000000LL, 100000000LL, "x2");
        inf.readSpace();
        long long y2 = inf.readLong(-100000000LL, 100000000LL, "y2");
        inf.readEoln();

        ensuref(x1 < x2, "rectangle %d must have x1 < x2, got %lld and %lld", i, x1, x2);
        ensuref(y1 > y2, "rectangle %d must have y1 > y2, got %lld and %lld", i, y1, y2);
    }

    inf.readEof();
}
