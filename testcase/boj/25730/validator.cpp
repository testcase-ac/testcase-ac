#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    long long a = inf.readLong(0LL, 1000000000000000000LL, "A");
    inf.readSpace();
    long long l = inf.readLong(0LL, 1000000000000000000LL, "L");
    inf.readSpace();
    long long r = inf.readLong(0LL, 1000000000000000000LL, "R");
    inf.readEoln();

    ensuref(l <= r, "L must not exceed R: L=%lld, R=%lld", l, r);

    inf.readEof();
}
