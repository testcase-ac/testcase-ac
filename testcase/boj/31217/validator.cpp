#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int maxM = min(1LL * n * (n - 1) / 2, 200000LL);
    int m = inf.readInt(0, maxM, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: (%d, %d)", i + 1, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: (%d, %d)", i + 1, u, v);
    }

    inf.readEof();
}
