#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MIN_N = 3;
    constexpr int MAX_N = 300000;
    constexpr int MIN_M = 1;
    constexpr int MAX_M = 300000;
    constexpr long long MIN_A = 1LL;
    constexpr long long MAX_A = 1000000000000000000LL;

    int n = inf.readInt(MIN_N, MAX_N, "n");
    inf.readSpace();
    int m = inf.readInt(MIN_M, MAX_M, "m");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readLong(MIN_A, MAX_A, "a_i");
    }
    inf.readEoln();

    for (int q = 1; q <= m; ++q) {
        inf.readInt(1, n, "i");
        inf.readSpace();
        inf.readLong(MIN_A, MAX_A, "x");
        inf.readEoln();
    }

    inf.readEof();
}
