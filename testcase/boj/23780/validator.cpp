#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int maxEdges = min(1LL * n * (n - 1) / 2, 20000LL);
    int m = inf.readInt(0, maxEdges, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 1000000, "v_i");
    }
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int f = inf.readInt(0, n - 1, "f_i");
        inf.readSpace();
        int t = inf.readInt(0, n - 1, "t_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "w_i");
        inf.readEoln();

        // CHECK: The M <= N(N-1)/2 bound describes an undirected simple graph.
        ensuref(f != t, "self-loop at edge %d: %d", i + 1, f);
        auto edge = minmax(f, t);
        ensuref(edges.insert(edge).second,
                "duplicate undirected edge at edge %d: (%d, %d)", i + 1, f, t);
    }

    inf.readEof();
}
