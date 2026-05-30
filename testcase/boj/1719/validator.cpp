#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 200, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "m");
    inf.readEoln();

    // To check connectivity, build adjacency list
    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int t = inf.readInt(1, 1000, "t_i");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge index %d: (%d, %d)", i + 1, a, b);
        adj[a].emplace_back(b, t);
        adj[b].emplace_back(a, t);
    }

    // Check that the graph is connected (undirected)
    if (n > 1) {
        vector<bool> vis(n + 1, false);
        vector<int> q;
        q.push_back(1);
        vis[1] = true;
        for (size_t i = 0; i < q.size(); ++i) {
            int u = q[i];
            for (auto& p : adj[u]) {
                int v = p.first;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push_back(v);
                }
            }
        }
        int cnt = 0;
        for (int i = 1; i <= n; ++i) if (vis[i]) ++cnt;
        ensuref(cnt == n, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, n);
    }

    inf.readEof();
}
