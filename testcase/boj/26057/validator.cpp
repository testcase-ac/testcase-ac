#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long l = inf.readLong(1LL, 1000000000LL, "L");
    inf.readEoln();
    long long t = inf.readLong(1LL, 1000000000LL, "T");
    inf.readEoln();

    ensuref(t <= l, "T must be at most L, got T=%lld and L=%lld", t, l);
    ensuref(l < 2 * t, "L must be less than 2*T, got L=%lld and T=%lld", l, t);

    inf.readEof();
}
