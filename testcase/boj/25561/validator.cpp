#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 1000000, "T");
    inf.readEoln();

    long long sumN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000, "n");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= 1000000LL, "sum of n exceeds 1000000");

        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                inf.readSpace();
            }
            inf.readLong(1LL, 1000000000LL, "c_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
