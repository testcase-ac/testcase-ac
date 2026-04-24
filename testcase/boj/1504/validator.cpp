#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices N and edges E
    int N = inf.readInt(2, 800, "N");
    inf.readSpace();
    int E = inf.readInt(0, 200000, "E");
    inf.readEoln();

    // Read edges, ensure no loops or multiple edges
    set<pair<int,int>> edges;
    for (int i = 0; i < E; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 1000, "c_i");
        inf.readEoln();

        // No self-loops
        ensuref(a != b, "Loop detected at edge index %d: (%d, %d)", i, a, b);

        // No multiple edges (undirected)
        int u = min(a, b), v = max(a, b);
        ensuref(!edges.count({u, v}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, a, b);
        edges.insert({u, v});
    }

    // Read the two mandatory vertices v1 and v2
    int v1 = inf.readInt(1, N, "v1");
    inf.readSpace();
    int v2 = inf.readInt(1, N, "v2");
    inf.readEoln();

    // Validate v1 and v2 constraints
    ensuref(v1 != v2, "v1 and v2 must be different: v1=%d, v2=%d", v1, v2);
    ensuref(v1 != N,   "v1 must not be N: v1=%d, N=%d", v1, N);
    ensuref(v2 != 1,   "v2 must not be 1: v2=%d", v2);

    // End of file
    inf.readEof();
    return 0;
}
