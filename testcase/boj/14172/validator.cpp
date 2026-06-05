#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 25000, "x_i");
        inf.readSpace();
        inf.readInt(0, 25000, "y_i");
        inf.readSpace();
        // CHECK: The statement omits an explicit bound for p. Since p is a
        // nonnegative transmission radius and all coordinates are in a
        // 25000-by-25000 square, 50000 is a practical cap above the full farm
        // diagonal.
        inf.readInt(0, 50000, "p_i");
        inf.readEoln();
    }

    inf.readEof();
}
