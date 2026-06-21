#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readLong(1LL, 1000000000LL, "a");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "b");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "c");
        inf.readEoln();
    }

    inf.readEof();
}
