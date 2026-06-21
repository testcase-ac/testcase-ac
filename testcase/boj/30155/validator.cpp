#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(-1000000000, 1000000000, "A");
        inf.readSpace();
        inf.readInt(-1000000000, 1000000000, "B");
        inf.readSpace();
        inf.readInt(1, 1000000000, "N");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
