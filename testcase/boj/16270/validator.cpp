#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 500, "t");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(1, 1000000000, "a");
        inf.readSpace();
        inf.readInt(1, 1000000000, "b");
        inf.readEoln();
    }

    inf.readEof();
}
