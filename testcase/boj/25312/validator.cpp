#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, 10000000000LL, "M");
    inf.readEoln();

    long long totalVolume = 0;
    for (int i = 1; i <= n; ++i) {
        int w = inf.readInt(1, 100000, "w_i");
        inf.readSpace();
        inf.readInt(1, 100000, "v_i");
        inf.readEoln();

        totalVolume += w;
    }

    ensuref(m <= totalVolume, "M must not exceed sum of w_i: M=%lld, sum=%lld", m, totalVolume);

    inf.readEof();
}
