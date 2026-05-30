#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readInt(2, 24, "n");
        inf.readSpace();
        inf.readInt(1, 1000000000, "k");
        inf.readEoln();
    }

    inf.readEof();
}
