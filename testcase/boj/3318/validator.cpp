#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no explicit upper bound for N. This cap keeps
    // scalar token count within local validator policy while preserving shape.
    int n = inf.readInt(2, 1000000, "N");
    inf.readSpace();
    long long d = inf.readLong(1LL, 1000000000LL, "D");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "size_i");
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
