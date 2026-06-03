#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readEoln();

    inf.readInts(n, 0, 10000, "A_i");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        long long s = inf.readLong(1LL, 1000000000LL, "S_i");
        inf.readSpace();
        long long e = inf.readLong(s, 1000000000LL, "E_i");
        inf.readEoln();
    }

    inf.readEof();
}
