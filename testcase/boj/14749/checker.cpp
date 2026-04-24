#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input (the tree and s, t)
    int n = inf.readInt(2, MAXN, "n");
    vector<vector<int>> g(n+1);
    for (int i = 0; i < n-1; i++) {
        int u = inf.readInt(1, n, "u");
        int v = inf.readInt(1, n, "v");
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int s = inf.readInt(1, n, "s");
    int t = inf.readInt(1, n, "t");
    if (s == t)
        inf.quitf(_fail, "s and t must be distinct");

    // Preprocess for LCA / distances
    int LOG = 0;
    while ((1 << LOG) <= n) LOG++;
    vector<int> depth(n+1, -1);
    vector<vector<int>> up(LOG, vector<int>(n+1, 1));
    // BFS from 1
    queue<int> q;
    depth[1] = 0;
    up[0][1] = 1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                q.push(v);
            }
        }
    }
    // Binary lifting
    for (int k = 1; k < LOG; k++) {
        for (int v = 1; v <= n; v++) {
            up[k][v] = up[k-1][ up[k-1][v] ];
        }
    }
    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a,b);
        int diff = depth[a] - depth[b];
        for (int k = 0; k < LOG; k++) {
            if (diff & (1<<k)) a = up[k][a];
        }
        if (a == b) return a;
        for (int k = LOG-1; k >= 0; k--) {
            if (up[k][a] != up[k][b]) {
                a = up[k][a];
                b = up[k][b];
            }
        }
        return up[0][a];
    };
    auto dist = [&](int a, int b) {
        int c = lca(a,b);
        return depth[a] + depth[b] - 2*depth[c];
    };

    // Read and validate contestant's route
    vector<bool> seen(n+1, false);
    vector<int> route;
    route.reserve(n);
    for (int i = 0; i < n; i++) {
        int v = ouf.readInt(1, n, format("vertex #%d", i+1).c_str());
        route.push_back(v);
        if (seen[v])
            ouf.quitf(_wa, "vertex %d appears more than once", v);
        seen[v] = true;
    }
    // Check no extra output
    if (!ouf.seekEof())
        ouf.quitf(_wa, "extra output after reading %d vertices", n);

    // Check all vertices are present
    for (int v = 1; v <= n; v++) {
        if (!seen[v])
            quitf(_wa, "vertex %d is missing in the route", v);
    }
    // Check start and end
    if (route.front() != s)
        quitf(_wa, "route should start at %d but starts at %d", s, route.front());
    if (route.back() != t)
        quitf(_wa, "route should end at %d but ends at %d", t, route.back());

    // Check jumps distances
    for (int i = 0; i + 1 < n; i++) {
        int u = route[i], v = route[i+1];
        int d = dist(u, v);
        if (d > 3)
            quitf(_wa, "jump from %d to %d has distance %d (>3)", u, v, d);
    }

    quitf(_ok, "valid grasshopper route");
}
