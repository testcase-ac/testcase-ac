#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of computers
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read number of possible connections
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Build adjacency for connectivity check
    vector<vector<int>> adj(N+1);
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 10000, "c_i");
        inf.readEoln();

        // loops allowed but do not contribute to connectivity
        if (a != b) {
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    // Check that the graph is connected
    if (N > 0) {
        vector<char> vis(N+1, false);
        queue<int> q;
        vis[1] = true;
        q.push(1);
        int seen = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    seen++;
                    q.push(v);
                }
            }
        }
        ensuref(seen == N,
                "The graph is not connected: only %d out of %d nodes are reachable",
                seen, N);
    }

    inf.readEof();
    return 0;
}
