#include "testlib.h"

bool isPowerOfTwo(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 1 << 20, "N");
    inf.readEoln();
    ensuref(isPowerOfTwo(n), "N must be a power of two: %d", n);

    inf.readLongs(n, 0LL, 1000000000LL, "a_i");
    inf.readEoln();

    int k = inf.readInt(1, n - 1, "k");
    inf.readEoln();
    ensuref(isPowerOfTwo(k), "k must be a power of two: %d", k);

    inf.readEof();
}
