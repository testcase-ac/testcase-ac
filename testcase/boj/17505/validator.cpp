#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 314159, "N");
    inf.readSpace();
    long long maxInversions = 1LL * n * (n - 1) / 2;
    inf.readLong(0LL, maxInversions, "K");
    inf.readEoln();
    inf.readEof();
}
