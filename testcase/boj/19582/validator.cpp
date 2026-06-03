#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "x_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "p_i");
        inf.readEoln();
    }

    inf.readEof();
}
