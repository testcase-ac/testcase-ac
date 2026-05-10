#include "testlib.h"
#include <set>
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 2000, "M");
    inf.readEoln();

    // Prepare to check for duplicate edges and self-loops
    set<pair<int, int>> edges;
    vector<vector<int>> adj(N);

    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(0, N - 1, "a");
        inf.readSpace();
        int b = inf.readInt(0, N - 1, "b");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i, a, b);

        int u = min(a, b), v = max(a, b);
        ensuref(!edges.count({u, v}), "Multiple edge detected between %d and %d at edge %d", u, v, i);
        edges.insert({u, v});

        // Build adjacency list for possible further checks
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    inf.readEof();
}
