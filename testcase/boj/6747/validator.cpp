#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 11, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 99, "N");
        inf.readSpace();
        // CHECK: The statement omits an explicit M bound; comparisons scale with ordered bead pairs.
        int m = inf.readInt(0, n * (n - 1), "M");
        inf.readEoln();

        ensuref(n % 2 == 1, "N must be odd, got %d", n);

        for (int i = 1; i <= m; ++i) {
            int heavier = inf.readInt(1, n, "heavier");
            inf.readSpace();
            int lighter = inf.readInt(1, n, "lighter");
            inf.readEoln();

            ensuref(heavier != lighter,
                    "comparison %d compares bead %d with itself", i, heavier);
        }
    }

    inf.readEof();
    return 0;
}
