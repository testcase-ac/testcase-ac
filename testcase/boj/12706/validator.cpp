#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(0, 1000, "C");
    inf.readEoln();

    for (int i = 1; i <= c; ++i) {
        setTestCase(i);

        int n = inf.readInt(1, 10000, "N");
        inf.readSpace();
        int m = inf.readInt(1, 10000, "M");
        inf.readSpace();
        inf.readInt(1, 100000000, "A");
        inf.readEoln();
    }

    inf.readEof();
}
