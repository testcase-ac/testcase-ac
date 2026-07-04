#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        int x = inf.readInt(-1000000, 1000000, "X");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "Y");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "target must not be (0, 0)");
    }

    inf.readEof();
}
