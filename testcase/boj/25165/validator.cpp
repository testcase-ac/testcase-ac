#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100, "M");
    inf.readEoln();

    int ac = inf.readInt(1, m, "A_c");
    inf.readSpace();
    int d = inf.readInt(0, 1, "D");
    inf.readEoln();

    int sr = inf.readInt(2, n, "S_r");
    inf.readSpace();
    int sc = inf.readInt(1, m, "S_c");
    inf.readEoln();

    ensuref(sr != n || sc != m, "monster position must not be the portal: (%d, %d)", sr, sc);

    inf.readEof();
}
