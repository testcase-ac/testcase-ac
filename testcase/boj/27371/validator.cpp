#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        int n = inf.readInt(1, 99999, "N");
        inf.readSpace();
        int m = inf.readInt(n + 1, 100000, "M");
        inf.readEoln();
    }

    inf.readEof();
}
