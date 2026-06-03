#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 150000, "N");
    inf.readEoln();

    inf.readInts(n, 0, 100000000, "a");
    inf.readEoln();

    int q = inf.readInt(1, 150000, "Q");
    inf.readEoln();

    for (int query = 1; query <= q; ++query) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(0, 100000000, "j");
        inf.readEoln();

        (void)i;
        (void)j;
    }

    inf.readEof();
}
