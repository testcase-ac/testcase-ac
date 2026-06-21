#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 51, "n");
    inf.readEoln();

    // CHECK: for N = 1 there are zero degree scores, so the score line is absent.
    if (n == 1) {
        inf.readEof();
        return 0;
    }

    for (int i = 1; i <= n - 1; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(0, 10000, "score_i");
    }
    inf.readEoln();
    inf.readEof();
}
