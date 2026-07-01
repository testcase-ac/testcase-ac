#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for T; local policy caps it.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalN = 0;
    int totalM = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100000, "m");
        inf.readEoln();

        totalN += n;
        totalM += m;
        ensuref(totalN <= 100000, "sum of n exceeds 100000");
        ensuref(totalM <= 100000, "sum of m exceeds 100000");

        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readEoln();

            ensuref(a != b, "person %d visits themselves in testcase %d visit %d", a, tc, i);
        }
    }

    inf.readEof();
}
