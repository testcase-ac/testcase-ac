#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int L;
    int K;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 2;
    const int N_MAX = 10000;
    const int M_MIN = 1;
    const int M_MAX = 100000;
    const int L_MIN = 1;
    const int L_MAX = 100000;
    const int K_MIN = 1;
    const int K_MAX = 10;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(M_MIN, M_MAX, "M");
    inf.readEoln();

    vector<vector<Edge>> g(N + 1);
    // Use set to prevent multi-edges (not specified, but common to disallow? Problem doesn't forbid.
    // So we DO NOT forbid multiple edges or loops unless specified.
    // However, loops don't make sense for shortest path with non-negative weights, but still allowed?
    // Statement doesn't forbid loops or multi-edges, so we must allow them. No extra structural check here.

    for (int i = 0; i < M; ++i) {
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readSpace();
        int L = inf.readInt(L_MIN, L_MAX, "L");
        inf.readSpace();
        int K = inf.readInt(K_MIN, K_MAX, "K");
        inf.readEoln();

        g[A].push_back({B, L, K});
        g[B].push_back({A, L, K});
    }

    // Check that there is at least one path from 1 to N, as guaranteed.
    // Because speed cannot go below 1 and edge speed limits K >= 1,
    // using speed = 1 everywhere is always feasible. So path existence
    // is purely graph connectivity between 1 and N.
    vector<char> vis(N + 1, 0);
    queue<int> q;
    vis[1] = 1;
    q.push(1);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto &e : g[v]) {
            if (!vis[e.to]) {
                vis[e.to] = 1;
                q.push(e.to);
            }
        }
    }
    ensuref(vis[N], "Graph must have at least one path from node 1 to node %d", N);

    inf.readEof();
}
