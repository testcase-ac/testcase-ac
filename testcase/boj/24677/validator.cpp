#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 1000000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        // CHECK: The statement imposes no self-loop or duplicate-pair restriction.
        (void)x;
        (void)y;
    }

    inf.readEof();
}
