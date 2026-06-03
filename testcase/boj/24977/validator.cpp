#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "v_i");
        inf.readEoln();

        ensuref(a != i, "a_%d must not be equal to %d", i, i);
    }

    inf.readEof();
}
