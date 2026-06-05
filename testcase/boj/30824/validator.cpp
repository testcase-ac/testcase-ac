#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 3, "k");
        inf.readSpace();
        inf.readLong(1LL, 10000000000000000LL, "x");
        inf.readEoln();
    }

    inf.readEof();
}
