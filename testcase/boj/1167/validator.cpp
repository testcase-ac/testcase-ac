#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int V = inf.readInt(2, 100000, "V");
    inf.readEoln();

    vector<bool> seen(V + 1, false);
    vector<vector<pair<int, int>>> adj(V + 1);
    map<pair<int, int>, vector<int>> weights_by_edge;

    for (int line = 1; line <= V; ++line) {
        int u = inf.readInt(1, V, "u");
        ensuref(!seen[u], "vertex %d is described more than once", u);
        seen[u] = true;

        set<int> neighbors;
        while (true) {
            inf.readSpace();
            int v = inf.readInt(-1, V, "v");
            if (v == -1) {
                break;
            }

            inf.readSpace();
            int w = inf.readInt(1, 10000, "w");
            ensuref(u != v, "self-loop in adjacency list for vertex %d", u);
            ensuref(neighbors.insert(v).second,
                    "duplicate neighbor %d in adjacency list for vertex %d", v, u);
            adj[u].push_back({v, w});
            weights_by_edge[{min(u, v), max(u, v)}].push_back(w);
        }
        inf.readEoln();
    }

    for (int u = 1; u <= V; ++u) {
        ensuref(seen[u], "vertex %d is not described", u);
    }

    ensuref((int)weights_by_edge.size() == V - 1,
            "tree must have exactly %d undirected edges, found %d",
            V - 1, (int)weights_by_edge.size());

    for (const auto& [edge, weights] : weights_by_edge) {
        ensuref(weights.size() == 2,
                "edge %d-%d must appear in both endpoint adjacency lists",
                edge.first, edge.second);
        ensuref(weights[0] == weights[1],
                "edge %d-%d has inconsistent weights %d and %d",
                edge.first, edge.second, weights[0], weights[1]);
    }

    vector<bool> visited(V + 1, false);
    queue<int> q;
    visited[1] = true;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto& [v, w] : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    for (int u = 1; u <= V; ++u) {
        ensuref(visited[u], "graph is disconnected: vertex %d is unreachable", u);
    }

    inf.readEof();
}
