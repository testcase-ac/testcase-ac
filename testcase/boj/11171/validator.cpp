#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        int n = inf.readInt(1, 1000, "N");
        inf.readSpace();
        int k = inf.readInt(1, n, "K");
        inf.readEoln();
    }

    inf.readEof();
}
