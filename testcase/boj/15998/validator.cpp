#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long MIN_AMOUNT = -1000000000000000000LL;
    constexpr long long MAX_AMOUNT = 1000000000000000000LL;

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long a = inf.readLong(MIN_AMOUNT, MAX_AMOUNT, "a_i");
        ensuref(a != 0, "a_%d must be nonzero", i);
        inf.readSpace();
        inf.readLong(0LL, MAX_AMOUNT, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
