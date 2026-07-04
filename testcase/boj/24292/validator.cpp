#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
