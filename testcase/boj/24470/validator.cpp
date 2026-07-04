#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 70, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "t_i");
        inf.readEoln();

        // CHECK: The statement does not forbid loops or duplicate directed routes.
        (void)a;
        (void)b;
    }

    inf.readInt(1, 1000000000, "k");
    inf.readSpace();
    int q = inf.readInt(1, n * n, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "c_j");
        inf.readSpace();
        inf.readInt(1, n, "d_j");
        inf.readEoln();
    }

    inf.readEof();
}
