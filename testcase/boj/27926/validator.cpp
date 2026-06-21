#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 300000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int d = inf.readInt(1, 1000000000, "d_i");
        inf.readEoln();

        ensuref(u < v, "edge %d has u_i >= v_i: %d >= %d", i, u, v);
        ensuref(edges.emplace(u, v).second,
                "duplicate synergy pair at edge %d: (%d, %d), d_i=%d",
                i,
                u,
                v,
                d);
    }

    inf.readEof();
}
