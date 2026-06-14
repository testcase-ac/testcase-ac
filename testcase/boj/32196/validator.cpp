#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "K");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "X");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "Y");
    inf.readEoln();

    long long sumB = 0;
    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 1000, "A_i");
        inf.readSpace();
        int b = inf.readInt(0, 1000, "B_i");
        inf.readEoln();

        sumB += b;
    }

    ensuref(sumB < k, "sum of B_i (%lld) must be less than K (%lld)", sumB, k);

    inf.readEof();
    return 0;
}
