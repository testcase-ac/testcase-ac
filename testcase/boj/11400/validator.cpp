#include "testlib.h"
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices and edges
    int V = inf.readInt(1, 100000, "V");
    inf.readSpace();
    int E = inf.readInt(1, 1000000, "E");
    inf.readEoln();

    // Read edges, detect loops
    vector<pair<int,int>> edges;
    edges.reserve(E);
    for (int i = 0; i < E; i++) {
        int a = inf.readInt(1, V, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, V, "B_i");
        inf.readEoln();
        ensuref(a != b,
                "Loop detected at edge index %d: (%d, %d)", i, a, b);
        int u = min(a, b), v = max(a, b);
        edges.emplace_back(u, v);
    }

    // Check for multiple edges
    sort(edges.begin(), edges.end());
    for (int i = 1; i < E; i++) {
        if (edges[i] == edges[i-1]) {
            int u = edges[i].first, v = edges[i].second;
            ensuref(false,
                    "Multiple edges detected between (%d, %d)", u, v);
        }
    }

    // Build adjacency list
    vector<vector<int>> adj(V+1);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    // Check connectivity via BFS
    vector<char> vis(V+1, 0);
    deque<int> dq;
    dq.push_back(1);
    vis[1] = 1;
    int cnt = 1;
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (int w : adj[u]) {
            if (!vis[w]) {
                vis[w] = 1;
                cnt++;
                dq.push_back(w);
            }
        }
    }
    ensuref(cnt == V,
            "Graph not connected: reachable %d out of %d vertices", cnt, V);

    inf.readEof();
    return 0;
}
