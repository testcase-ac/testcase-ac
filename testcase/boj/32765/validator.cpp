#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000LL, "X");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readLong(1LL, 1000000000LL, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
