#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(0, 1000, "C");
    inf.readEoln();

    for (int i = 1; i <= c; ++i) {
        setTestCase(i);

        inf.readInt(1, 50, "N");
        inf.readSpace();
        inf.readInt(1, 50, "M");
        inf.readSpace();
        inf.readInt(1, 100000000, "A");
        inf.readEoln();
    }

    inf.readEof();
}
