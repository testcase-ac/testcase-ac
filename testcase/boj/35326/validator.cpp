#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readLong(0LL, 1000000000LL, "A");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "B");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "c_A");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "c_B");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "f_A");
        inf.readEoln();
    }

    inf.readEof();
}
