#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 250, "n");
    inf.readSpace();
    int maxM = n * (n - 1) / 2;
    int m = inf.readInt(0, maxM, "m");
    inf.readEoln();

    // Prepare for checking duplicate edges and connectivity
    vector<vector<bool>> seen(n+1, vector<bool>(n+1, false));
    vector<int> parent(n+1);
    iota(parent.begin(), parent.end(), 0);
    function<int(int)> find = [&](int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    };
    auto unite = [&](int a, int b) {
        a = find(a); b = find(b);
        if (a != b) parent[b] = a;
    };

    // Read edges
    for (int i = 0; i < m; i++) {
        char buf[32];
        sprintf(buf, "u_%d", i);
        int u = inf.readInt(1, n, buf);
        inf.readSpace();
        sprintf(buf, "v_%d", i);
        int v = inf.readInt(1, n, buf);
        inf.readSpace();
        sprintf(buf, "b_%d", i);
        int b = inf.readInt(0, 1, buf);
        inf.readEoln();

        // No self-loops
        ensuref(u != v,
                "Loop detected at edge index %d: u = v = %d", i, u);

        // No multiple edges between same pair (undirected sense)
        int a = min(u, v), c = max(u, v);
        ensuref(!seen[a][c],
                "Multiple edges detected between %d and %d at index %d", a, c, i);
        seen[a][c] = true;

        // Union for connectivity (undirected)
        unite(u, v);
    }

    // Check that the undirected graph is connected
    if (n > 1) {
        int root1 = find(1);
        for (int i = 2; i <= n; i++) {
            ensuref(find(i) == root1,
                    "Graph is not connected: node %d is unreachable", i);
        }
    }

    // Read queries
    int k = inf.readInt(1, 30000, "k");
    inf.readEoln();
    for (int i = 0; i < k; i++) {
        char buf[32];
        sprintf(buf, "s_%d", i);
        int s = inf.readInt(1, n, buf);
        inf.readSpace();
        sprintf(buf, "e_%d", i);
        int e = inf.readInt(1, n, buf);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
