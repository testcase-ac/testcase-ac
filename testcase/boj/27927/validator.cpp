#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "m");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long s = inf.readLong(1LL, m, "s_i");
        inf.readSpace();
        inf.readLong(s, m, "e_i");
        inf.readEoln();
    }

    inf.readEof();
}
