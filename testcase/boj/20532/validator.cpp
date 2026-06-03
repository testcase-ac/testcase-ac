#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    inf.readInts(n, 1, 100000, "a");
    inf.readEoln();

    if (n == 1) {
        // CHECK: the parent-list line has zero integers; accept EOF after A[1]
        // because fixed input materialization may drop a blank-only final line.
        if (inf.seekEof()) {
            inf.readEof();
            return 0;
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            if (i > 2) {
                inf.readSpace();
            }
            inf.readInt(1, i - 1, "p");
        }
    }
    inf.readEoln();

    inf.readEof();
}
