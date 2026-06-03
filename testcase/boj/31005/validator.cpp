#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000000LL, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000000LL, "A_i");
        if (i < n) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    inf.readEof();
}
