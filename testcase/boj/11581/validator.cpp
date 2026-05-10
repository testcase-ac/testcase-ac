#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // 2. For i = 1 to N-1, read M_i and C_i
    vector<vector<int>> adj(N + 1); // 1-based indexing
    for (int i = 1; i <= N - 1; ++i) {
        int M_i = inf.readInt(0, N, "M_" + to_string(i));
        inf.readEoln();

        if (M_i > 0) {
            vector<int> C_i = inf.readInts(M_i, 1, N, "C_" + to_string(i));
            inf.readEoln();

            // Check for duplicate edges from i
            set<int> s;
            for (int j = 0; j < M_i; ++j) {
                int v = C_i[j];
                ensuref(s.count(v) == 0, "Duplicate outgoing edge from node %d to node %d", i, v);
                s.insert(v);
                adj[i].push_back(v);
            }
        }
    }

    // N-th node (shelter) must have no outgoing edges
    // No input for N-th node, so nothing to check

    // 3. Check for self-loops
    for (int u = 1; u <= N - 1; ++u) {
        for (int v : adj[u]) {
            ensuref(u != v, "Self-loop detected at node %d", u);
        }
    }

    // 4. Check that all nodes are reachable from node 1 (optional, not required by statement)
    // Not required: the problem does not require the graph to be connected.

    // 5. Check for whitespace strictness: nothing extra on lines, etc. Already enforced by readEoln/readInts.

    // 6. Check for global property: nothing in statement says "the answer always exists" or "always NO CYCLE", so nothing to check here.

    inf.readEof();
}
