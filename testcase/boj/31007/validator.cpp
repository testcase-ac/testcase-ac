#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    int sumN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 150, "N");
        inf.readSpace();
        int m = inf.readInt(1, 100000, "M");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= 150, "sum of N exceeds 150 after test case %d", tc);

        for (int i = 1; i <= m; ++i) {
            inf.readInt(1, n, "card");
            if (i == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
