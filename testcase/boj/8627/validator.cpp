#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    inf.readInt(1, n, "p");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "s");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
