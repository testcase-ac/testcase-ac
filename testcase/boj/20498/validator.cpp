#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 262143, "N");
    inf.readEoln();

    ensuref((n & (n + 1)) == 0, "N must be 2^k - 1, found %d", n);

    inf.readLongs(n, 1LL, 100000000LL, "W_i");
    inf.readEoln();
    inf.readEof();
}
