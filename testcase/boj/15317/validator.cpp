#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    long long x = inf.readLong(0LL, 1000000000LL, "X");
    inf.readEoln();

    inf.readLongs(n, 0LL, 1000000000LL, "C_i");
    inf.readEoln();

    inf.readLongs(m, 0LL, 1000000000LL, "S_i");
    inf.readEoln();

    inf.readEof();
}
