#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readLong(1LL, n, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
