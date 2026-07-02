#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for N; cap scalar tokens below
    // the local practical limit while preserving the same input shape.
    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        // CHECK: The statement gives no coordinate bounds; accept signed
        // 32-bit-scale coordinates because the event point must be integral.
        inf.readInt(-1000000000, 1000000000, "X_i");
        inf.readSpace();
        inf.readInt(-1000000000, 1000000000, "Y_i");
        inf.readEoln();
    }

    inf.readEof();
}
