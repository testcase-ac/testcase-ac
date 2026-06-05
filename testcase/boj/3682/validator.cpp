#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 20000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 50000, "m");
        inf.readEoln();

        for (int i = 1; i <= m; ++i) {
            int s1 = inf.readInt(1, n, "s1");
            inf.readSpace();
            int s2 = inf.readInt(1, n, "s2");
            inf.readEoln();

            ensuref(s1 != s2, "self implication at testcase %d edge %d: %d", tc, i, s1);
        }
    }

    inf.readEof();
}
