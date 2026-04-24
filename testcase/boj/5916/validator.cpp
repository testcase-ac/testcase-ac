#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read the tree edges, check for loops and multiple edges
    set<pair<int,int>> seen_edges;
    vector<vector<int>> adj(N+1);
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v,
                "Loop detected at edge index %d: (%d, %d)", i, u, v);

        pair<int,int> e = make_pair(min(u,v), max(u,v));
        ensuref(!seen_edges.count(e),
                "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);

        seen_edges.insert(e);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Check connectivity of the tree
    vector<char> vis(N+1, 0);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    int cnt = 1;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) {
            if (!vis[y]) {
                vis[y] = 1;
                cnt++;
                q.push(y);
            }
        }
    }
    ensuref(cnt == N,
            "Graph is disconnected: only %d out of %d nodes are reachable from node 1",
            cnt, N);

    // Read and validate queries
    for (int i = 0; i < M; i++) {
        // Query type: must be 'P' or 'Q'
        string t = inf.readToken("[PQ]", "type");
        inf.readSpace();
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();
        // No further checks: solution handles update/query logic
    }

    inf.readEof();
    return 0;
}
