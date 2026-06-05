#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const long long MAX_STAT = 100000000LL;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int m = inf.readInt(1, n + 1, "M");
    (void)m;
    inf.readEoln();

    inf.readLong(1LL, MAX_STAT, "V_0");
    inf.readSpace();
    inf.readLong(1LL, MAX_STAT, "P_0");
    inf.readSpace();
    inf.readLong(1LL, MAX_STAT, "S_0");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, MAX_STAT, "V_i");
        inf.readSpace();
        inf.readLong(1LL, MAX_STAT, "P_i");
        inf.readSpace();
        inf.readLong(1LL, MAX_STAT, "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
