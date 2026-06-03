#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(2, 1000000, "N");
        inf.readSpace();
        int a = inf.readInt(2, 100000, "A");
        inf.readSpace();
        int b = inf.readInt(a, 100000, "B");
        inf.readEoln();
    }

    inf.readEof();
}
