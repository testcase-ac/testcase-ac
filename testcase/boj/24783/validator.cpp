#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        inf.readInt(1, 10000, "a");
        inf.readSpace();
        inf.readInt(1, 10000, "b");
        inf.readSpace();
        inf.readInt(1, 10000, "c");
        inf.readEoln();
    }

    inf.readEof();
}
