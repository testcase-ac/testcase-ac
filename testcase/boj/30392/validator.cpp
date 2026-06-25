#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 500000, "M");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "v_i");
        inf.readSpace();
        inf.readInt(1, n, "w_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
