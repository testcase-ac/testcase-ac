#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "N");
    ensuref(n % 2 == 0, "N must be even: %d", n);
    inf.readSpace();
    long long maxK = (1LL << n) - 1;
    inf.readLong(0LL, maxK, "K");
    inf.readEoln();
    inf.readEof();
}
