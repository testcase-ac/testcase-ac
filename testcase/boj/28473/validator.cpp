#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "M");
    inf.readEoln();

    long long maxEdges = 1LL * n * (n - 1) / 2;
    ensuref(m <= maxEdges, "M=%d exceeds the maximum number of simple undirected edges for N=%d", m, n);

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readSpace();
        int z = inf.readInt(1, 9, "z");
        inf.readSpace();
        int w = inf.readInt(0, 1000000, "w");
        inf.readEoln();

        ensuref(x != y, "self-loop at edge %d: %d %d", i, x, y);
        pair<int, int> edge = minmax(x, y);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, x, y);
        (void)z;
        (void)w;
    }

    inf.readEof();
}
