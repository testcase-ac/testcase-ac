#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

// Helper function to check connectivity using BFS
void check_connected(const vector<vector<int>>& adj, int n) {
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

// Helper function to find the unique cycle (the circular line)
vector<int> find_cycle(const vector<vector<int>>& adj, int n) {
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);
    vector<int> cycle;
    function<bool(int, int)> dfs = [&](int u, int p) -> bool {
        visited[u] = true;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (visited[v]) {
                // Found a cycle, backtrack
                cycle.push_back(v);
                int cur = u;
                while (cur != v) {
                    cycle.push_back(cur);
                    cur = parent[cur];
                }
                reverse(cycle.begin(), cycle.end());
                return true;
            } else {
                parent[v] = u;
                if (dfs(v, u)) return true;
            }
        }
        return false;
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfs(i, -1)) break;
        }
    }
    ensuref(!cycle.empty(), "No cycle found in the graph");
    // Check that the cycle is simple (no repeated nodes except start/end)
    set<int> cycset(cycle.begin(), cycle.end());
    ensuref(cycset.size() == cycle.size(), "Cycle is not simple");
    return cycle;
}

// Helper function to check the structure of the graph
void check_structure(const vector<vector<int>>& adj, int n) {
    // 1. There must be exactly one simple cycle (the circular line)
    vector<int> cycle = find_cycle(adj, n);
    int cyc_len = cycle.size();
    ensuref(cyc_len >= 3, "Cycle length must be at least 3, got %d", cyc_len);

    // 2. All other edges must be trees attached to the cycle (no other cycles)
    // Remove cycle edges, then check for cycles in the rest
    vector<vector<int>> adj2 = adj;
    for (int i = 0; i < cyc_len; ++i) {
        int u = cycle[i], v = cycle[(i+1)%cyc_len];
        // Remove u-v and v-u
        adj2[u].erase(find(adj2[u].begin(), adj2[u].end(), v));
        adj2[v].erase(find(adj2[v].begin(), adj2[v].end(), u));
    }
    // Now, adj2 contains only the branches
    vector<bool> vis(n, false);
    for (int i = 0; i < n; ++i) {
        if (find(cycle.begin(), cycle.end(), i) != cycle.end()) continue;
        if (!vis[i]) {
            // BFS from i, check for cycles
            queue<pair<int,int>> q;
            q.push({i, -1});
            vis[i] = true;
            while (!q.empty()) {
                int u = q.front().first, p = q.front().second; q.pop();
                for (int v : adj2[u]) {
                    if (v == p) continue;
                    if (vis[v]) {
                        ensuref(false, "Branch attached to cycle contains a cycle (node %d <-> %d)", u+1, v+1);
                    }
                    vis[v] = true;
                    q.push({v, u});
                }
            }
        }
    }
    // 3. Each branch must be attached to the cycle at exactly one node
    // For each node in the cycle, count the number of attached branches
    // (A branch is a connected component in adj2 rooted at a cycle node)
    vector<bool> vis2(n, false);
    for (int cycnode : cycle) {
        for (int v : adj2[cycnode]) {
            if (!vis2[v]) {
                // BFS from v
                queue<int> q;
                q.push(v);
                vis2[v] = true;
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    for (int w : adj2[u]) {
                        if (!vis2[w]) {
                            vis2[w] = true;
                            q.push(w);
                        }
                    }
                }
            }
        }
    }
    // All non-cycle nodes must be visited in vis2
    for (int i = 0; i < n; ++i) {
        if (find(cycle.begin(), cycle.end(), i) == cycle.end()) {
            ensuref(vis2[i], "Node %d is not attached to the cycle", i+1);
        }
    }
    // 4. Each branch is a tree, and each non-cycle node has degree at least 1
    for (int i = 0; i < n; ++i) {
        if (find(cycle.begin(), cycle.end(), i) == cycle.end()) {
            ensuref(adj2[i].size() >= 1, "Non-cycle node %d has degree < 1", i+1);
        }
    }
    // 5. Each branch is attached to the cycle at exactly one node
    // (already checked by construction above)
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 3000, "n");
    inf.readEoln();

    set<pair<int,int>> edges;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
        ensuref(u != v, "Self-loop detected at line %d: (%d, %d)", i+2, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Multiple edge detected at line %d: (%d, %d)", i+2, u, v);
        edges.insert({a, b});
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }
    ensuref(int(edges.size()) == n, "Number of edges must be exactly n, got %d", int(edges.size()));

    // Check connectivity
    check_connected(adj, n);

    // Check structure: exactly one simple cycle, all other parts are trees attached to the cycle
    check_structure(adj, n);

    inf.readEof();
}
