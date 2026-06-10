#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "w_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "d_i");
        inf.readEoln();
    }

    inf.readEof();
}
