#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, m, "cpu");
        inf.readSpace();
        inf.readInt(1, k, "memory");
        inf.readSpace();
        inf.readInt(1, 5, "priority");
        inf.readEoln();
    }

    inf.readEof();
}
