#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read V, E, P
    int V = inf.readInt(2, 5000, "V");
    inf.readSpace();
    int E = inf.readInt(1, 10000, "E");
    inf.readSpace();
    int P = inf.readInt(1, V, "P");
    inf.readEoln();

    // 2. Prepare adjacency list, and check for duplicate/loop edges
    vector<vector<pair<int,int>>> adj(V+1); // 1-based
    set<pair<int,int>> edge_set;

    for (int i = 0; i < E; ++i) {
        int a = inf.readInt(1, V, "a");
        inf.readSpace();
        int b = inf.readInt(1, V, "b");
        inf.readSpace();
        int c = inf.readInt(1, 10000, "c");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i+1, a, b);
        int u = min(a, b), v = max(a, b);
        ensuref(!edge_set.count({u, v}), "Multiple edge detected at edge %d: (%d, %d)", i+1, a, b);
        edge_set.insert({u, v});

        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    // 3. Check that 1 can reach both P and V (guaranteed by statement, must validate)
    // Use BFS for reachability
    auto bfs = [&](int start) -> vector<bool> {
        vector<bool> vis(V+1, false);
        queue<int> q;
        vis[start] = true;
        q.push(start);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &pr : adj[u]) {
                int v = pr.first;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        return vis;
    };

    vector<bool> vis = bfs(1);
    ensuref(vis[P], "Vertex P=%d is not reachable from 1", P);
    ensuref(vis[V], "Vertex V=%d is not reachable from 1", V);

    inf.readEof();
}
