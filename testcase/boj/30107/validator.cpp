#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 500000, "N");
        inf.readSpace();
        inf.readInt(1, 500000, "A");
        inf.readSpace();
        inf.readInt(1, 500000, "B");
        inf.readEoln();
    }

    inf.readEof();
}
