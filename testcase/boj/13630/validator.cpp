#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(5LL, 1000000000000000LL, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000LL, "K");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000LL, "L");
    inf.readEoln();

    ensuref(n % 5 == 0, "N must be a multiple of 5, got %lld", n);

    inf.readEof();
}
