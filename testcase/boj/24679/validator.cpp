#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 200000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readLong(1LL, 1000000000LL, "x");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "y");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "z");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
