#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readLong(1LL, 1000000000000000000LL, "n");
        inf.readEoln();
    }

    inf.readEof();
}
