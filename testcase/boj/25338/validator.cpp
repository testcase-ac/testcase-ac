#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(-10, -1, "a");
    inf.readSpace();
    int b = inf.readInt(1, 10000, "b");
    inf.readSpace();
    int c = inf.readInt(1, 10000, "c");
    inf.readSpace();
    int d = inf.readInt(1, 9999, "d");
    inf.readEoln();
    ensuref(d < c, "expected d < c, got d=%d and c=%d", d, c);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int u = inf.readInt(d + 1, c, "u_i");
        inf.readSpace();
        int v = inf.readInt(b, 10000, "v_i");
        inf.readEoln();
    }

    inf.readEof();
}
