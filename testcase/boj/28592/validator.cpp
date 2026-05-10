#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // 2. Read v_i
    vector<int> v(N+1); // 1-based
    for (int i = 1; i <= N; ++i) {
        v[i] = inf.readInt(1, 1000000000, "v_i");
        if (i < N) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read N-1 edges, check for valid tree (no loops, no multi-edges, connected)
    set<pair<int,int>> edges;
    vector<vector<int>> adj(N+1);
    for (int i = 0; i < N-1; ++i) {
        int x = inf.readInt(1, N, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readEoln();

        ensuref(x != y, "Loop detected at edge index %d: (%d, %d)", i+1, x, y);
        int a = min(x, y), b = max(x, y);
        ensuref(!edges.count({a, b}), "Multiple edge detected at edge index %d: (%d, %d)", i+1, x, y);
        edges.insert({a, b});
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    // Check connectedness using BFS
    vector<bool> vis(N+1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int vtx : adj[u]) {
            if (!vis[vtx]) {
                vis[vtx] = true;
                q.push(vtx);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d/%d nodes reachable from node 1", cnt, N);

    // 4. Read Q queries
    for (int i = 0; i < Q; ++i) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readEoln();
        // No further constraints on a_i, b_i
    }

    inf.readEof();
}
