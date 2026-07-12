#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The provided statement excerpt has no test-count bound, so use the local default.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 50, "n");
        inf.readSpace();
        int k = inf.readInt(0, n, "k");
        inf.readEoln();

        int previous = 0;
        for (int i = 1; i <= k; ++i) {
            if (i > 1) {
                inf.readSpace();
            }

            int value = inf.readInt(1, n, "combination_element");
            ensuref(value > previous,
                    "combination elements must be strictly increasing, got %d after %d",
                    value,
                    previous);
            previous = value;
        }
        inf.readEoln();
    }

    inf.readEof();
}
