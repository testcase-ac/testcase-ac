#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int k = inf.readInt(0, 12000, "K");
    inf.readSpace();
    int l = inf.readInt(0, 4000, "L");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        setTestCase(i + 1);

        inf.readInt(0, 4000, "x1");
        inf.readSpace();
        inf.readInt(0, 4000, "x2");
        inf.readSpace();
        inf.readInt(0, 4000, "x3");
        inf.readEoln();
    }

    inf.readEof();
}
