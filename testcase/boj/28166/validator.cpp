#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long sumN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 200000, "n");
        inf.readEoln();
        sumN += n;
        ensuref(sumN <= 200000, "sum of n exceeds 200000 after test case %d", tc);

        int p1 = inf.readInt(0, 0, "p_1");
        for (int i = 2; i <= n; ++i) {
            inf.readSpace();
            inf.readInt(1, i - 1, "p_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
