#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(0, 10000, "P");
        inf.readSpace();
        inf.readInt(0, 10000, "Q");
        inf.readSpace();
        inf.readInt(1, 10000, "A");
        inf.readSpace();
        inf.readInt(1, 10000, "B");
        inf.readSpace();
        inf.readInt(1, 10000, "C");
        inf.readSpace();
        inf.readInt(1, 10000, "D");
        inf.readEoln();
    }

    inf.readEof();
}
