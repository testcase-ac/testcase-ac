#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    long long maxPairs = 1LL * n * (n - 1) / 2;
    inf.readLong(0LL, maxPairs, "K");
    inf.readEoln();

    inf.readEof();
}
