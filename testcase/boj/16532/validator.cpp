#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 50000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int n = inf.readInt(2, 100000, "N");
        inf.readSpace();
        int k = inf.readInt(2, 100000, "K");
        inf.readEoln();

        (void)n;
        (void)k;
    }

    inf.readEof();
}
