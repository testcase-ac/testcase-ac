#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readSpace();
    inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, 100000, "c");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d %d", i + 1, a, b);
    }

    inf.readEof();
}
