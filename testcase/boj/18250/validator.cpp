#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities N and number of routes M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300000, "M");
    inf.readEoln();

    // To check for duplicate edges
    set<pair<int,int>> edges;
    edges.clear();

    for (int i = 0; i < M; i++) {
        // Read each edge (u, v)
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        // No loops allowed: u != v
        ensuref(u != v,
                "Loop detected at edge index %d: (%d, %d)",
                i, u, v);

        // Normalize edge representation
        int a = min(u, v), b = max(u, v);
        pair<int,int> e = make_pair(a, b);

        // No multiple edges allowed
        ensuref(!edges.count(e),
                "Multiple edges detected at edge index %d: (%d, %d)",
                i, u, v);

        edges.insert(e);
    }

    // No extra content after the last newline
    inf.readEof();
    return 0;
}
