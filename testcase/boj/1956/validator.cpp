#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices V and edges E
    int V = inf.readInt(2, 400, "V");
    inf.readSpace();
    int maxE = V * (V - 1); // maximum possible directed edges without loops
    int E = inf.readInt(0, maxE, "E");
    inf.readEoln();

    // Validate each directed edge
    set<pair<int,int>> edges;
    for (int i = 0; i < E; i++) {
        int a = inf.readInt(1, V, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, V, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 10000, "c_i");
        inf.readEoln();

        // No self‐loops allowed (since maximum edges is V*(V-1))
        ensuref(a != b,
                "Self-loop detected at edge index %d: (%d -> %d)", i, a, b);

        // No multiple edges between same ordered pair
        ensuref(!edges.count({a, b}),
                "Multiple edges detected at edge index %d: (%d -> %d)", i, a, b);

        edges.insert({a, b});
    }

    inf.readEof();
    return 0;
}
