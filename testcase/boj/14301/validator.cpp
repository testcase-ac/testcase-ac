#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 100, "R");
        inf.readSpace();
        inf.readInt(1, 100, "C");
        inf.readEoln();
    }

    inf.readEof();
}
