#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 10000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);
        inf.readInt(1, n, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
