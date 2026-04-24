#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    // Read edges
    vector<pair<int,int>> edges;
    edges.reserve(max(0, n - 1));
    for (int i = 0; i < n - 1; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v,
                "Loop detected on edge %d: (%d, %d)",
                i + 1, u, v);

        int a = min(u, v);
        int b = max(u, v);
        edges.emplace_back(a, b);
    }

    // Check for duplicate edges
    sort(edges.begin(), edges.end());
    for (size_t i = 1; i < edges.size(); i++) {
        if (edges[i] == edges[i-1]) {
            ensuref(false,
                    "Multiple edges detected: (%d, %d) appears more than once",
                    edges[i].first, edges[i].second);
        }
    }

    // Build adjacency list
    vector<vector<int>> adj(n + 1);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // BFS from root=1 to check connectivity, acyclicity, and binary property
    vector<char> vis(n + 1, 0);
    vector<int> parent(n + 1, 0);
    vector<int> q;
    q.reserve(n);

    q.push_back(1);
    vis[1] = 1;
    parent[1] = 0;

    size_t qi = 0;
    while (qi < q.size()) {
        int u = q[qi++];
        int childCount = 0;
        for (int v : adj[u]) {
            if (v == parent[u]) {
                // skip edge back to parent
                continue;
            }
            if (vis[v]) {
                // found a back-edge => cycle
                ensuref(false,
                        "Cycle detected via edge (%d, %d)",
                        u, v);
            }
            parent[v] = u;
            vis[v] = 1;
            q.push_back(v);
            childCount++;
        }
        // In a rooted binary tree, each node has at most 2 children
        ensuref(childCount <= 2,
                "Node %d has %d children, but maximum is 2",
                u, childCount);
    }

    // Check connectivity
    ensuref((int)q.size() == n,
            "Graph is not connected: reachable nodes = %d, expected = %d",
            (int)q.size(), n);

    inf.readEof();
    return 0;
}
