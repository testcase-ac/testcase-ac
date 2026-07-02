#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "A");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "B");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(2, 1000000000, "a_i");
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
