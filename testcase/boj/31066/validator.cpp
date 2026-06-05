#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(1, 10, "N");
        inf.readSpace();
        inf.readInt(1, 10, "M");
        inf.readSpace();
        inf.readInt(1, 10, "K");
        inf.readEoln();
    }

    inf.readEof();
}
