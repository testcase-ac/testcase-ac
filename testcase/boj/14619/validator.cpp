#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readEoln();

    inf.readInts(n, 0, 10000, "H");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "X");
        inf.readSpace();
        int y = inf.readInt(1, n, "Y");
        inf.readEoln();

        ensuref(x != y, "bridge %d is a self-loop at island %d", i, x);
        // CHECK: The statement does not forbid duplicate bridges, so parallel
        // bridges are accepted.
    }

    // CHECK: The statement asks what to print when no island is reachable after
    // exactly K moves, so disconnected graphs are accepted.
    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        inf.readInt(1, n, "A");
        inf.readSpace();
        inf.readInt(1, 500, "K");
        inf.readEoln();
    }

    inf.readEof();
}
