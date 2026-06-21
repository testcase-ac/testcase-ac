#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readLong(1LL, 1000000000000000000LL, "n");
        inf.readSpace();
        inf.readLong(1LL, 1000000000000000000LL, "d");
        inf.readEoln();
    }

    inf.readEof();
}
