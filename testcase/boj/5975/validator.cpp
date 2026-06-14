#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The archived statement text is corrupted around the upper bound;
    // the reference solution's fixed array size and recovered fragment support 1 <= N <= 100.
    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readEoln();

    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            if (c > 1) {
                inf.readSpace();
            }
            inf.readInt(0, 1, "C_rc");
        }
        inf.readEoln();
    }

    inf.readEof();
}
