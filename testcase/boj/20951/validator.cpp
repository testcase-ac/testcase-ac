#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, min(1LL * n * (n - 1) / 2, 100000LL), "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d %d", i, u, v);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: %d %d", i, u, v);
    }

    inf.readEof();
}
