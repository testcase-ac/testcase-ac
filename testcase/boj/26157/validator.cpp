#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 500000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        int w = inf.readInt(1, n, "w");
        inf.readEoln();

        ensuref(v != w, "self-loop at edge %d: %d -> %d", i, v, w);
        // CHECK: The statement forbids v == w but does not forbid duplicate directed edges.
    }

    inf.readEof();
}
