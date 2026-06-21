#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 100000, "sum of N exceeds 100000 after test case %d", tc);

        for (int i = 1; i <= n; ++i) {
            inf.readInt(1, 100000, "s_i");
            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
