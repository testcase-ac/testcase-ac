#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement only gives an upper bound for N, but N is the number
    // of prospective buyers, so the empty instance is not treated as valid.
    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 1000000, "max_price");
        inf.readSpace();
        inf.readInt(0, 1000000, "delivery_cost");
        inf.readEoln();
    }

    inf.readEof();
}
