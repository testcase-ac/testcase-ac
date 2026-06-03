#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    int m = inf.readInt(1, n * (n - 1) / 2, "M");
    inf.readSpace();
    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readSpace();
    int c = inf.readInt(1, 10000, "C");
    inf.readEoln();

    ensuref(a != b, "A and B must be different: A=%d, B=%d", a, b);

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int cost = inf.readInt(1, 1000, "cost_i");
        inf.readEoln();

        ensuref(u != v, "edge %d connects the same intersection: %d", i, u);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate edge at index %d: (%d, %d)", i, u, v);
        (void)cost;
    }

    inf.readEof();
}
