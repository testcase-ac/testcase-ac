#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 600000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(1, 100000, "a");
        inf.readSpace();
        inf.readInt(1, 100000, "b");
        inf.readSpace();
        inf.readInt(1, 100000, "c");
        inf.readEoln();
    }

    inf.readEof();
}
