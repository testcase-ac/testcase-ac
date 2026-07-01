#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 100, "n");
        inf.readSpace();
        inf.readLong(1LL, 1000000000000000000LL, "k");
        inf.readEoln();
    }

    inf.readEof();
}
