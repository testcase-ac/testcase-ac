#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 200000, "K");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    inf.readInts(m, 1, 200000, "height_limit");
    inf.readEoln();

    inf.readInts(k, 1, n, "growing_child");
    inf.readEoln();

    for (int query = 1; query <= q; ++query) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readSpace();
        int ride = inf.readInt(1, m, "ride");
        inf.readEoln();

        // CHECK: The statement gives only 1 <= i, j <= N, so pairs with i == j are accepted.
        (void)i;
        (void)j;
        (void)ride;
    }

    inf.readEof();
}
