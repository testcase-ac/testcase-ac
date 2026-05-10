#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices N and edges M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    // M must satisfy 0 ≤ M ≤ N*(N-1)/2
    int maxM = N * (N - 1) / 2;
    int M = inf.readInt(0, maxM, "M");
    inf.readEoln();

    // Validate edges: undirected, no loops, no duplicates
    set<pair<int,int>> seen;
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        ensuref(u != v,
                "Loop detected at edge index %d: (%d,%d)", i, u, v);
        ensuref(!seen.count({u, v}),
                "Multiple edges detected at edge index %d: (%d,%d)", i, u, v);

        // mark both directions to catch (v,u) later
        seen.insert({u, v});
        seen.insert({v, u});
    }

    inf.readEof();
    return 0;
}
