#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long l = inf.readLong(0LL, 2000000000LL, "l");
    inf.readSpace();
    long long u = inf.readLong(0LL, 2000000000LL, "u");
    inf.readEoln();

    ensuref(l <= u, "l must not exceed u: l=%lld, u=%lld", l, u);

    inf.readEof();
}
