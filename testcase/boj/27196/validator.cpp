#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 500000, "n");
    inf.readEoln();
    ensuref(n % 2 == 1, "n must be odd, got %d", n);

    for (int i = 0; i < n; ++i) {
        inf.readLong(1LL, 1000000000LL, "a_i");
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
