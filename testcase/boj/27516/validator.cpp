#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_COORD = -100000000LL;
    const long long MAX_COORD = 100000000LL;

    long long x = inf.readLong(MIN_COORD, MAX_COORD, "x");
    inf.readSpace();
    long long y = inf.readLong(MIN_COORD, MAX_COORD, "y");
    inf.readEoln();

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long xi = inf.readLong(MIN_COORD, MAX_COORD, "x_i");
        inf.readSpace();
        long long yi = inf.readLong(MIN_COORD, MAX_COORD, "y_i");
        inf.readEoln();

        ensuref(xi != x || yi != y,
                "target %d is at the observer coordinate (%lld, %lld)",
                i, xi, yi);
    }

    inf.readEof();
}
