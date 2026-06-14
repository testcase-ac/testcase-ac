#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000000000000LL, "M");
    inf.readSpace();
    long long maxK = 1LL * n * (n + 1) / 2;
    inf.readLong(1LL, maxK, "K");
    inf.readEoln();

    inf.readInts(n, 0, 1000000000, "A_i");
    inf.readEoln();

    inf.readEof();
}
