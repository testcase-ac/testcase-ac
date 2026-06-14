#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long l = inf.readLong(-1000000000LL, 1000000000LL, "l_i");
        inf.readSpace();
        long long r = inf.readLong(l, 1000000000LL, "r_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "v_i");
        inf.readEoln();
    }

    inf.readEof();
}
