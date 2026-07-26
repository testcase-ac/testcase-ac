#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500, "N");
    inf.readSpace();
    int maxM = n * (n - 1) / 2;
    int m = inf.readInt(n - 1, maxM, "M");
    inf.readEoln();

    vector<vector<int>> adj(n + 1);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "edge %d is a loop: %d %d", i, u, v);
        if (u > v) swap(u, v);
        ensuref(edges.insert({u, v}).second, "duplicate edge %d: %d %d", i, u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> seen(n + 1, 0);
    queue<int> q;
    seen[1] = 1;
    q.push(1);
    int reached = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ++reached;
        for (int nxt : adj[cur]) {
            if (!seen[nxt]) {
                seen[nxt] = 1;
                q.push(nxt);
            }
        }
    }
    ensuref(reached == n, "graph is not connected: reached %d of %d vertices", reached, n);

    inf.readEof();
    return 0;
}
