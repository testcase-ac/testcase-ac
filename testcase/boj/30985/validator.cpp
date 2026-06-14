#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readSpace();
    inf.readInt(2, 200000, "K");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 100000000, "c");
        inf.readEoln();

        ensuref(u != v, "loop at edge %d: %d", i + 1, u);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate corridor at edge %d: (%d, %d)", i + 1, u, v);
    }

    for (int i = 0; i < n; ++i) {
        int e = inf.readInt(-1, 100000000, "e_i");
        ensuref(e == -1 || e >= 1,
                "invalid elevator time at room %d: %d", i + 1, e);
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
