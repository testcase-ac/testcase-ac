#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices
    int V = inf.readInt(2, 100000, "V");
    inf.readEoln();

    // Track which vertices have been described
    vector<bool> seen(V+1, false);
    // Adjacency list: for each u, store pairs (v, w)
    vector<vector<pair<int,int>>> adj(V+1);

    // Read V lines of adjacency info
    for (int i = 0; i < V; i++) {
        // Line index in file is i+2 (since first line is V)
        int u = inf.readInt(1, V, "u");
        ensuref(!seen[u],
                "Vertex %d is described more than once (line %d)", 
                u, i+2);
        seen[u] = true;

        // Read pairs v, w until we see v == -1
        while (true) {
            inf.readSpace();
            int v = inf.readInt(-1, V, "v");
            if (v == -1) break;
            inf.readSpace();
            int w = inf.readInt(1, 10000, "w");

            // No self-loops
            ensuref(u != v,
                    "Loop detected at line %d: (%d,%d)", 
                    i+2, u, v);

            adj[u].push_back({v, w});
        }
        inf.readEoln();
    }

    // Ensure every vertex 1..V was described exactly once
    for (int u = 1; u <= V; u++) {
        ensuref(seen[u],
                "Vertex %d is not described in input", 
                u);
    }

    // Within each adjacency list, no duplicate neighbors
    for (int u = 1; u <= V; u++) {
        auto &lst = adj[u];
        vector<int> vs;
        vs.reserve(lst.size());
        for (auto &p : lst) vs.push_back(p.first);
        sort(vs.begin(), vs.end());
        for (int i = 1; i < (int)vs.size(); i++) {
            ensuref(vs[i] != vs[i-1],
                    "Multiple edges in adjacency list of vertex %d: (%d,%d)",
                    u, vs[i-1], vs[i]);
        }
    }

    // Collect undirected edges, ensure exactly V-1 and no parallel edges
    set<pair<int,int>> edges;
    for (int u = 1; u <= V; u++) {
        for (auto &p : adj[u]) {
            int v = p.first;
            if (u < v) {
                auto e = make_pair(u, v);
                ensuref(!edges.count(e),
                        "Multiple edges detected: (%d,%d)", 
                        u, v);
                edges.insert(e);
            }
        }
    }
    ensuref((int)edges.size() == V-1,
            "Number of edges is %d but expected %d", 
            (int)edges.size(), V-1);

    // Check connectivity via BFS from vertex 1
    vector<char> vis(V+1, 0);
    queue<int> q;
    vis[1] = 1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &p : adj[u]) {
            int v = p.first;
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    for (int u = 1; u <= V; u++) {
        ensuref(vis[u],
                "Graph is disconnected: vertex %d is unreachable", 
                u);
    }

    inf.readEof();
    return 0;
}
