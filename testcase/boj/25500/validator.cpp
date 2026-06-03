#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 200000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(0LL, 1000000000LL, "x_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "y_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "z_i");
        inf.readEoln();
    }

    inf.readEof();
}
