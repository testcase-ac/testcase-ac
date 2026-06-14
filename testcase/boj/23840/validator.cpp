#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(10, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(10, 300000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 1000000, "w");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop: %d %d", i, u, v);
    }

    int x = inf.readInt(1, n, "X");
    inf.readSpace();
    int z = inf.readInt(1, n, "Z");
    inf.readEoln();

    ensuref(x != z, "X and Z must be different: %d", x);

    int p = inf.readInt(3, min(20, n - 3), "P");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= p; ++i) {
        if (i > 1) {
            inf.readSpace();
        }

        int y = inf.readInt(1, n, "Y");
        ensuref(y != x, "intermediate vertex %d equals X: %d", i, y);
        ensuref(y != z, "intermediate vertex %d equals Z: %d", i, y);
        ensuref(!seen[y], "duplicate intermediate vertex %d: %d", i, y);
        seen[y] = true;
    }
    inf.readEoln();

    inf.readEof();
}
