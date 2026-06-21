#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "target_price");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 10000000, "C_i");
        inf.readSpace();
        inf.readInt(1, 3, "discount_i");
        inf.readEoln();
    }

    inf.readEof();
}
