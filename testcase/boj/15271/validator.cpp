#include "testlib.h"

#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200, "N");
    inf.readSpace();
    int m = inf.readInt(0, min(10000, n * (n - 1) / 2), "M");
    inf.readEoln();

    set<pair<int, int>> seen;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d is a loop: %d %d", i, u, v);
        auto edge = minmax(u, v);
        ensuref(seen.insert(edge).second, "duplicate undirected edge %d: %d %d", i, u, v);
    }

    inf.readEof();
}
