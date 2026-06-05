#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readLong(1LL, 1000000000LL, "N");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "K");
        inf.readEoln();
    }

    inf.readEof();
}
