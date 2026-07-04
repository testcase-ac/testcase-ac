#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long l = inf.readLong(1LL, 1000000000000LL, "L");
    inf.readSpace();
    long long r = inf.readLong(1LL, 1000000000000LL, "R");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000LL, "Q");
    inf.readEoln();

    ensuref(l <= r, "L must be at most R: L=%lld, R=%lld", l, r);

    inf.readEof();
    return 0;
}
