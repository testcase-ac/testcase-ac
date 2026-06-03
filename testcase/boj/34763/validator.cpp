#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readLong(1LL, 1000000000LL, "N");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "K");
        inf.readEoln();
    }

    inf.readEof();
}
