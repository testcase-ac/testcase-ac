#include "testlib.h"
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m, k
    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int maxEdges = n * (n - 1) / 2;
    int m = inf.readInt(0, maxEdges, "m");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000000000000LL, "k");
    inf.readEoln();

    // Validate edges: undirected, no loops, no duplicates
    set<pair<int,int>> edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v,
                "Loop detected at edge index %d: (%d, %d)",
                i, u, v);

        int a = min(u, v);
        int b = max(u, v);
        ensuref(!edges.count({a, b}),
                "Multiple edges detected at edge index %d: (%d, %d)",
                i, a, b);

        edges.insert({a, b});
    }

    inf.readEof();
    return 0;
}
