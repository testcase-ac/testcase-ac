#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of farms
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read edges
    vector<pair<int,int>> edges;
    edges.reserve(max(0, N-1));
    set<pair<int,int>> seen;
    for (int i = 0; i < N-1; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readEoln();

        // No loops
        ensuref(a != b,
                "Loop detected at edge index %d: (%d, %d)", i, a, b);
        // No multiple edges (undirected)
        int u = min(a, b), v = max(a, b);
        ensuref(!seen.count({u, v}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
        seen.insert({u, v});

        edges.emplace_back(a, b);
    }

    // Check connectivity using BFS from node 1
    vector<vector<int>> adj(N+1);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    vector<char> vis(N+1, 0);
    queue<int> q;
    vis[1] = 1;
    q.push(1);
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cnt++;
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    ensuref(cnt == N,
            "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, N);

    inf.readEof();
    return 0;
}
