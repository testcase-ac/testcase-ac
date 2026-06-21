#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        // CHECK: The Korean BOJ statement allows 0 <= V, X <= 50000, while the
        // English MooFest variant says both values are in 1..50000.
        inf.readInt(0, 50000, "v_i");
        inf.readSpace();
        // CHECK: The Korean BOJ statement does not require unique coordinates,
        // while the English MooFest variant says x coordinates are unique.
        inf.readInt(0, 50000, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
