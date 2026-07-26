#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    long long l = inf.readLong(0LL, 1000000000LL, "l");
    inf.readSpace();
    long long r = inf.readLong(l, 1000000000LL, "r");
    inf.readEoln();
    ensuref(r - l <= 100, "r - l must be at most 100");

    inf.readLongs(n, 0LL, 1000000000LL, "a_i");
    inf.readEoln();
    inf.readEof();
}
