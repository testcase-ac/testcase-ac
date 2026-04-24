#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m, n, k
    int m = inf.readInt(0, 300000, "m");
    inf.readSpace();
    int n = inf.readInt(1, 30000, "n");
    inf.readSpace();
    int k = inf.readInt(0, 500000, "k");
    inf.readEoln();
    // m ≤ 10n
    ensuref((ll)m <= 10ll * n,
            "Constraint violated: m (%d) > 10 * n (%d)", m, n);

    // Read source v and destination w
    int v = inf.readInt(0, n - 1, "v");
    inf.readSpace();
    int w = inf.readInt(0, n - 1, "w");
    inf.readEoln();

    // Prepare to read edges
    vector<vector<int>> adj(n);
    vector<int> outdeg(n, 0), indeg(n, 0);

    for (int i = 0; i < m; i++) {
        int x = inf.readInt(0, n - 1, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, n - 1, "y_i");
        ensuref(x != y, "Loop detected on edge %d: (%d, %d)", i, x, y);
        inf.readSpace();
        int c = inf.readInt(0, 1000, "c_i");
        inf.readEoln();
        // Track degrees
        outdeg[x]++;
        indeg[y]++;
        ensuref(outdeg[x] <= 10,
                "Out-degree limit exceeded at vertex %d: %d > 10", x, outdeg[x]);
        adj[x].push_back(y);
    }
    // Compute possible forbidden turns = sum indeg[y] * outdeg[y]
    ll possible = 0;
    for (int u = 0; u < n; u++) {
        possible += (ll)indeg[u] * outdeg[u];
    }
    ensuref((ll)k <= possible,
            "Constraint violated: k (%d) > possible forbidden turns (%lld)", k, possible);

    // Sort adjacency lists for fast lookup
    for (int u = 0; u < n; u++) {
        sort(adj[u].begin(), adj[u].end());
    }

    // Read forbidden turns
    unordered_set<ll> seen;
    seen.reserve(k * 2 + 1);
    for (int i = 0; i < k; i++) {
        int x = inf.readInt(0, n - 1, "fx_i");
        inf.readSpace();
        int y = inf.readInt(0, n - 1, "fy_i");
        inf.readSpace();
        int z = inf.readInt(0, n - 1, "fz_i");
        inf.readEoln();
        // Check edges exist: (x,y) and (y,z)
        bool has_xy = binary_search(adj[x].begin(), adj[x].end(), y);
        ensuref(has_xy,
                "Forbidden turn at index %d: edge (%d,%d) does not exist", i, x, y);
        bool has_yz = binary_search(adj[y].begin(), adj[y].end(), z);
        ensuref(has_yz,
                "Forbidden turn at index %d: edge (%d,%d) does not exist", i, y, z);
        // Check duplicate forbidden turn
        // encode triple as x * n^2 + y * n + z
        ll key = (ll)x * n * n + (ll)y * n + z;
        ensuref(!seen.count(key),
                "Duplicate forbidden turn at index %d: (%d, %d, %d)", i, x, y, z);
        seen.insert(key);
    }

    inf.readEof();
    return 0;
}
