#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        inf.readLong(6LL, 1000000000000000000LL, "Z");
        inf.readEoln();
    }

    inf.readEof();
}
