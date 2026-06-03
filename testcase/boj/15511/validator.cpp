#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int f = inf.readInt(1, n, "f_i");
        inf.readSpace();
        int s = inf.readInt(1, n, "s_i");
        inf.readEoln();

        ensuref(f != s, "self-loop at pair %d: (%d, %d)", i, f, s);
    }

    inf.readEof();
}
