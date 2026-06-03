#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);

        inf.readLong(0LL, 1000000000000000000LL, "x");
        inf.readSpace();
        inf.readLong(0LL, 1000000000000000000LL, "y");
        inf.readEoln();
    }

    inf.readEof();
}
