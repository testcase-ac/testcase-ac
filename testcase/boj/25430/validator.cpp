#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // 2. Prepare to check for multiple edges and self-loops
    set<tuple<int,int,int>> edge_set; // (min(a,b), max(a,b), w) for uniqueness
    vector<vector<pair<int,int>>> adj(N+1); // for connectivity check

    // 3. Read M edges
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readSpace();
        int w = inf.readInt(1, 10000000, "w");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i+1, a, b);

        // For multiple edges: allow multiple edges between same nodes if weights differ
        auto key = make_tuple(min(a,b), max(a,b), w);
        ensuref(!edge_set.count(key), "Duplicate edge detected at edge %d: (%d, %d, %d)", i+1, a, b, w);
        edge_set.insert(key);

        // For connectivity check
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }

    // 4. Read start and end
    int s = inf.readInt(1, N, "start");
    inf.readSpace();
    int t = inf.readInt(1, N, "end");
    inf.readEoln();

    // 5. Check that s != t is NOT required by statement

    // 6. Check that s and t are in [1, N] (already done above)

    // 7. Check for global formatting: EOF
    inf.readEof();

    // 8. Connectivity check: The problem does NOT guarantee that the graph is connected.
    //    So, we do NOT need to check for connectivity.

    // 9. Subtask 1: If M == N-1, check that the edges form a path 1-2-3-...-N
    if (M == N-1) {
        // Check that all edges are (i, i+1) for i=1..N-1
        vector<bool> found(N, false); // found[i] = edge (i, i+1) exists
        for (const auto& e : edge_set) {
            int u = get<0>(e);
            int v = get<1>(e);
            if (v-u == 1 && u >= 1 && v <= N) {
                found[u-1] = true;
            }
        }
        for (int i = 1; i < N; ++i) {
            ensuref(found[i-1], "For subtask 1: missing edge (%d, %d)", i, i+1);
        }
        // Also ensure no extra edges
        ensuref((int)edge_set.size() == N-1, "For subtask 1: extra edges exist");
    }

    // 10. No further global properties to check

    return 0;
}
