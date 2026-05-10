#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m
    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    // Prepare adjacency list
    vector<vector<pair<int, int>>> adj(n + 1); // 1-based, stores (neighbor, color)

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 1000000000, "c_i");
        inf.readEoln();

        // Add edge both ways (undirected)
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    // Check that 1 and n are not isolated
    ensuref(!adj[1].empty(), "Room 1 (entrance) must have at least one corridor.");
    ensuref(!adj[n].empty(), "Room n (exit) must have at least one corridor.");

    // Check that the graph is connected from 1 to n (as per problem guarantee)
    // BFS from 1, see if n is reachable
    vector<bool> vis(n + 1, false);
    queue<int> q;
    vis[1] = true;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : adj[u]) {
            int v = e.first;
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    ensuref(vis[n], "Room n (%d) is not reachable from room 1.", n);

    inf.readEof();
}
