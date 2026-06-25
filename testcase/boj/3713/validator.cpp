#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        // CHECK: The statement only gives N <= 500; a pupil set must be non-empty.
        int n = inf.readInt(1, 500, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            // CHECK: The statement gives no upper bound for a height in cm; cap to int-scale input.
            inf.readInt(0, 1000000000, "h");
            inf.readSpace();
            inf.readToken("M|F", "sex");
            inf.readSpace();
            inf.readToken("[^]{1,100}", "music");
            inf.readSpace();
            inf.readToken("[^]{1,100}", "sport");
            inf.readEoln();
        }
    }

    inf.readEof();
}
