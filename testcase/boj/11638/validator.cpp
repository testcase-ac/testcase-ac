#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 50000, "n");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readInt(1, 2 * n, "p_i");
            inf.readSpace();
            inf.readInt(1, 2 * n, "q_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
