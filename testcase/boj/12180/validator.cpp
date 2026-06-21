#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(1, 10, "R");
        inf.readSpace();
        inf.readInt(1, 10, "C");
        inf.readEoln();
    }

    inf.readEof();
}
