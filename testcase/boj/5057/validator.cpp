#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 10000, "m");
    inf.readEoln();

    inf.readInts(n, 1, 100, "p_i");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(0, n - 1, "u");
        inf.readSpace();
        int v = inf.readInt(0, n - 1, "v");
        inf.readSpace();
        inf.readInt(1, 100, "d");
        inf.readEoln();

        // CHECK: The statement bounds u and v but does not forbid loops or parallel roads.
        (void)u;
        (void)v;
    }

    int q = inf.readInt(1, 100, "q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, 100, "c");
        inf.readSpace();
        inf.readInt(0, n - 1, "s");
        inf.readSpace();
        inf.readInt(0, n - 1, "e");
        inf.readEoln();
    }

    inf.readEof();
}
