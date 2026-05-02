#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(3, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(N-1, 200000, "M");
    inf.readEoln();

    // 2. Read M edges
    // Multiple edges allowed, self-loops not allowed
    vector<vector<int>> adj(N+1); // 1-based
    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "C1");
        inf.readSpace();
        int v = inf.readInt(1, N, "C2");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 3. Check that the graph is connected
    vector<bool> vis(N+1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d/%d nodes reachable from node 1", cnt, N);

    inf.readEof();
}
