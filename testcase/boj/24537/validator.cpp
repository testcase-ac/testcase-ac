#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 1000000, "A_i");
    }
    inf.readEoln();

    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, 1000000, "K_i");
        inf.readEoln();
    }

    inf.readEof();
}
