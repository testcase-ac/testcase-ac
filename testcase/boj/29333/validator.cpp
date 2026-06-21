#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readSpace();
    int s = inf.readInt(1, n, "S");
    inf.readSpace();
    int e = inf.readInt(1, n, "E");
    inf.readEoln();

    ensuref(s != e, "S and E must be different: %d", s);

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at vertex %d", i, u);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate undirected edge %d between vertices %d and %d",
                i, edge.first, edge.second);
    }

    inf.readEof();
}
