#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "X_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "Y_i");
        inf.readEoln();
    }

    inf.readEof();
}
