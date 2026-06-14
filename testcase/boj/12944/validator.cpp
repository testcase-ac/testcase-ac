#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 20, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        // CHECK: The statement says 1 <= i <= N, but the input gives K card values.
        inf.readInt(1, 1000000000, "A_i");
    }
    inf.readEoln();

    inf.readEof();
}
