#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readToken("[+*]", "op_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "k_i");
        inf.readEoln();
    }

    for (int j = 1; j <= q; ++j) {
        inf.readInt(1, n, "i_j");
        inf.readSpace();
        inf.readToken("[+*]", "op_j");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "k_j");
        inf.readEoln();
    }

    inf.readEof();
}
