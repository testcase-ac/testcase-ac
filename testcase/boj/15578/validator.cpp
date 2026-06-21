#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 200000, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, 2000000000LL, "K");
    inf.readSpace();
    long long m = inf.readLong(1LL, 2000000000LL, "M");
    inf.readEoln();
    ensuref(k <= m, "K must not exceed M: K=%lld, M=%lld", k, m);

    inf.readEof();
}
