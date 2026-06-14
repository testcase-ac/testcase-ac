#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readLong(2LL, 100000000000000LL, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
