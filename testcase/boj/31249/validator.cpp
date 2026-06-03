#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);
        inf.readInt(1, 1000000000, "n");
        inf.readSpace();
        inf.readInt(1, 1000000000, "m");
        inf.readEoln();
    }

    inf.readEof();
}
