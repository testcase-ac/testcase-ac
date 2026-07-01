#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    long long totalWork = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "N");
        inf.readSpace();
        int m = inf.readInt(1, 200000, "M");
        inf.readEoln();

        totalWork += n + m;
        // CHECK: The statement bounds T per file but gives no aggregate cap.
        ensuref(totalWork <= 300000,
                "sum of N + M over all test cases exceeds 300000");

        for (int i = 1; i <= m; ++i) {
            int x = inf.readInt(1, n, "X");
            inf.readSpace();
            int y = inf.readInt(1, n, "Y");
            inf.readEoln();

            ensuref(x != y, "self wish at test case %d, wish %d", tc, i);
        }
    }

    inf.readEof();
    return 0;
}
