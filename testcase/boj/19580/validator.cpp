#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxCount = 500000;
    const long long maxMoney = 1000000000000000000LL;

    int n = inf.readInt(1, maxCount, "N");
    inf.readSpace();
    int m = inf.readInt(1, maxCount, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long l = inf.readLong(1LL, maxMoney, "L_i");
        inf.readSpace();
        long long r = inf.readLong(1LL, maxMoney, "R_i");
        inf.readEoln();

        ensuref(l <= r, "citizen %d has L_i > R_i: %lld > %lld", i, l, r);
    }

    for (int j = 1; j <= m; ++j) {
        inf.readLong(1LL, maxMoney, "P_j");
        inf.readSpace();
        inf.readInt(1, 1000, "X_j");
        inf.readEoln();
    }

    inf.readEof();
}
