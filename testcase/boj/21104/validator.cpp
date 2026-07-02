#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long l = inf.readLong(1LL, 1000000000LL, "l_i");
        inf.readSpace();
        long long r = inf.readLong(l, 1000000000LL, "r_i");
        inf.readEoln();
    }

    for (int i = 1; i <= m; ++i) {
        inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
