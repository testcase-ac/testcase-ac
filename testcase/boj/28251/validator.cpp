#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    inf.readInts(n, 0, 2000, "s_i");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "query %d has equal endpoints: %d", i, a);
    }

    inf.readEof();
}
