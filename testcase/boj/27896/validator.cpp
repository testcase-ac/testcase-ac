#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "m");
    inf.readEoln();

    inf.readLongs(n, 0LL, 1000000000LL, "x_i");
    inf.readEoln();

    inf.readEof();
}
