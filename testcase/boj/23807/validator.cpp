#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(10, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(10, 300000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 1000000, "w");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d %d", i, u, v);
    }

    int x = inf.readInt(1, n, "x");
    inf.readSpace();
    int z = inf.readInt(1, n, "z");
    inf.readEoln();
    ensuref(x != z, "x and z must be distinct: %d", x);

    int p = inf.readInt(3, min(100, n - 3), "p");
    inf.readEoln();

    set<int> seen;
    for (int i = 1; i <= p; ++i) {
        int y = inf.readInt(1, n, "y");
        if (i < p) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }

        ensuref(y != x, "intermediate vertex %d equals x: %d", i, y);
        ensuref(y != z, "intermediate vertex %d equals z: %d", i, y);
        ensuref(seen.insert(y).second, "duplicate intermediate vertex %d: %d", i, y);
    }

    inf.readEof();
}
