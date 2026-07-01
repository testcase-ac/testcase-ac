#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long l = inf.readLong(1LL, 1000000000000000000LL, "L");
    inf.readSpace();
    long long r = inf.readLong(1LL, 1000000000000000000LL, "R");
    inf.readEoln();

    ensuref(l <= r, "expected L <= R, got L=%lld and R=%lld", l, r);

    inf.readEof();
}
