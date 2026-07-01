#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "a_i");
        inf.readSpace();
        inf.readInt(1, n, "b_i");
        inf.readSpace();
        inf.readInt(0, 10000, "t_i");
        inf.readEoln();
    }
    // CHECK: The statement does not forbid self-loops or duplicate teleport trips.

    for (int i = 1; i <= 7; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, n, "c_i");
    }
    inf.readEoln();

    inf.readEof();
}
