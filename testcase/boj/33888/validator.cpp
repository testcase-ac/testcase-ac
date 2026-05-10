#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

// Check that the graph is connected
void check_connected(int n, const vector<vector<int>>& adj) {
    vector<bool> vis(n, false);
    queue<int> q;
    q.push(0);
    vis[0] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                cnt++;
            }
        }
    }
    ensuref(cnt == n, "Graph is not connected: only %d/%d nodes reachable from node 1", cnt, n);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(6, 50, "n");
    inf.readEoln();

    int m = n + 3;
    set<pair<int,int>> edge_set;
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edge_set.count({a, b}), "Multiple edge detected at edge %d: (%d, %d)", i+1, u, v);
        edge_set.insert({a, b});
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Check connectivity
    check_connected(n, adj);

    // Degree constraints: 6 core nodes (deg != 2), rest deg==2
    int cnt_core = 0, cnt_deg2 = 0;
    vector<int> core_nodes;
    for (int i = 0; i < n; ++i) {
        int d = adj[i].size();
        ensuref(d >= 1 && d <= n-1, "Node %d has invalid degree %d", i+1, d);
        if (d == 2) cnt_deg2++;
        else {
            cnt_core++;
            core_nodes.push_back(i);
        }
    }
    ensuref(cnt_core == 6, "There must be exactly 6 core nodes (deg != 2), found %d", cnt_core);
    ensuref(cnt_deg2 == n-6, "There must be exactly N-6 nodes with degree 2, found %d", cnt_deg2);

    // All non-core nodes must have degree 2
    set<int> core_set(core_nodes.begin(), core_nodes.end());
    for (int i = 0; i < n; ++i) {
        if (!core_set.count(i)) {
            ensuref(adj[i].size() == 2, "Non-core node %d does not have degree 2", i+1);
        }
    }

    // All edges are unique and no self-loops (already checked above)

    inf.readEof();
}
