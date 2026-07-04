#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 299, "n");
        inf.readEoln();
        ensuref(n % 2 == 1, "n must be odd, got %d", n);

        for (int i = 1; i <= n; ++i) {
            inf.readInt(-10000, 10000, "x");
            inf.readSpace();
            inf.readInt(-10000, 10000, "y");
            inf.readEoln();
        }
    }

    inf.readEof();
}
