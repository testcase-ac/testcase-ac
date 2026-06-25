#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readInt(2, 1000000, "n");
        inf.readSpace();
        inf.readInt(1, 1000000000, "G");
        inf.readSpace();
        inf.readInt(1, 1000000000, "L");
        inf.readEoln();
    }

    inf.readEof();
}
