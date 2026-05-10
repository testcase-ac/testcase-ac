#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, A, B
    int N = inf.readInt(4, 300000, "N");
    inf.readSpace();
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readEoln();

    ensuref(A != B, "A (%d) and B (%d) must be different", A, B);

    // 2. Read N-1 edges
    vector<vector<int>> adj(N + 1); // 1-based
    set<pair<int, int>> edges;
    for (int i = 0; i < N - 1; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i + 1, u, v);

        int uu = min(u, v), vv = max(u, v);
        ensuref(edges.count({uu, vv}) == 0, "Multiple edge detected at edge %d: (%d, %d)", i + 1, u, v);
        edges.insert({uu, vv});

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 3. Check that the graph is connected (i.e., is a tree)
    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : adj[cur]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                q.push(nxt);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, N);

    // 4. Check that there are exactly N-1 edges (already ensured by input reading loop)

    inf.readEof();
}
