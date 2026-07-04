#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 200000, "T");
    inf.readEoln();

    long long sumN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200000, "n");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "m");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= 200000LL, "sum of n exceeds 200000 after test case %d", tc);

        for (int i = 1; i <= n; ++i) {
            inf.readLong(1LL, 1000000000LL, "t_i");
            inf.readSpace();
            inf.readLong(1LL, 1000000000LL, "h_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
