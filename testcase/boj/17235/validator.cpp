#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
