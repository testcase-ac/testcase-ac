#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int v = inf.readInt(1, 3000, "V");
    inf.readSpace();
    int e = inf.readInt(v, 3000, "E");
    inf.readEoln();

    set<pair<int, int>> edges;
    vector<int> degree(v + 1, 0);

    for (int i = 1; i <= e; ++i) {
        int a = inf.readInt(1, v, "V_a");
        inf.readSpace();
        int b = inf.readInt(1, v, "V_b");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop at vertex %d", i, a);

        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate connection segment at edge %d: (%d, %d)",
                i, edge.first, edge.second);

        ++degree[a];
        ++degree[b];
    }

    for (int i = 1; i <= v; ++i) {
        ensuref(degree[i] > 0, "vertex %d has no incident connection segment", i);
    }

    inf.readEof();
    return 0;
}
