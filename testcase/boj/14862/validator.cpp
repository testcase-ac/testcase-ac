#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int k = inf.readInt(2, 5, "K");
        inf.readEoln();

        for (int i = 1; i <= k; ++i) {
            int a = inf.readInt(1, 200000, "A_i");
            inf.readSpace();
            int b = inf.readInt(1, 200000, "B_i");
            inf.readEoln();
            ensuref(a <= b, "A_%d must be <= B_%d, got %d > %d", i, i, a, b);
        }
    }

    inf.readEof();
}
