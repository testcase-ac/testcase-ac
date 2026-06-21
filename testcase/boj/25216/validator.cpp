#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 50000, "M");
    inf.readSpace();
    inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000000, format("a_%d", i));
        inf.readSpace();
        inf.readInt(1, 10000, format("x_%d", i));
        inf.readSpace();
        inf.readInt(1, 10000, format("y_%d", i));
        inf.readSpace();
        inf.readInt(1, 10000, format("c_%d", i));
        inf.readEoln();
    }

    set<pair<int, int>> portals;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, format("u_%d", i));
        inf.readSpace();
        int v = inf.readInt(1, n, format("v_%d", i));
        inf.readEoln();

        ensuref(u != v, "portal %d is a self-loop: %d -> %d", i, u, v);
        ensuref(portals.insert({u, v}).second,
                "duplicate portal at index %d: %d -> %d", i, u, v);
    }

    inf.readEof();
}
