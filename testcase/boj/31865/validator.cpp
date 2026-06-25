#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "N");
    inf.readEoln();

    for (int i = 2; i <= n; ++i) {
        inf.readInt(1, i - 1, "p_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
