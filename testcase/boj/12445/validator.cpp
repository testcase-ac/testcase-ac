#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 500, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 1000, "A");
        inf.readSpace();
        inf.readInt(1, 2, "B");
        inf.readSpace();
        inf.readInt(1, 1000, "C");
        inf.readEoln();
    }

    inf.readEof();
}
