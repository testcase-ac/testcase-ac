#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 3, "breed");
        inf.readEoln();
    }

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(a, n, "b");
        inf.readEoln();
    }

    inf.readEof();
}
