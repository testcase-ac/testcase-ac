#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            // CHECK: The statement gives no matrix-entry bounds; this cap keeps
            // the full N x N integer matrix input practical while accepting
            // ordinary signed 32-bit-sized coefficients.
            long long value = inf.readLong(-1000000000LL, 1000000000LL, "A_ij");
            if (j + 1 < i || i + 1 < j) {
                ensuref(value == 0,
                        "A[%d][%d] must be zero outside the tridiagonal band, got %lld",
                        i + 1, j + 1, value);
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
