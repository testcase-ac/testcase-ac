#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    long long d = inf.readLong(1LL, 1000000000LL, "D");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long t = inf.readLong(1LL, d, "T_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "A_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
