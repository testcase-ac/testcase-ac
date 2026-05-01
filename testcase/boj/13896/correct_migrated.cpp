#include <iostream>
#include <array>
#include <vector>
#include <utility>

using namespace std;

struct Query { int v, i; };

struct Tree {
    array<int, 100'000> sz, depth;
    array<array<int, 17>, 100'000> jump;
    array<vector<int>, 100'000> adj;
    
    int n;
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) { adj[i].clear(); }
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int r) {
        auto fill_info = [&](auto self, int u, int p) -> void {
            sz[u] = 1;
            depth[u] = depth[p] + 1;
            jump[u][0] = p;
            for (int v : adj[u]) {
                if (v == p) { continue; }
                self(self, v, u);
                sz[u] += sz[v];
            }
        };

        depth[0] = -1;
        fill_info(fill_info, r, r);
        
        for (int k = 1; k < 17; k++) {
            for (int v = 0; v < n; v++) {
                jump[v][k] = jump[jump[v][k-1]][k-1];
            }
        }
    }

    struct ResultType { int lca, prev; };
    ResultType lca_prev(int a, int b) {
        if (a == b) { return { a, -1 }; };

        int prev = a;
        if (depth[a] != depth[b]) {
            if (depth[a] < depth[b]) { swap(a, b); }
            
            int steps = depth[a] - depth[b] - 1;
            for (int i = 16; i >= 0; i--) {
                if (steps & (1 << i)) { a = jump[a][i]; }
            }
            prev = a;
            a = jump[a][0];
        }

        if (a != b) {
            for (int i = 16; i >= 0; i--) {
                if (jump[a][i] != jump[b][i]) {
                    a = jump[a][i];
                    b = jump[b][i];
                }
            }
            prev = -1;
            a = jump[a][0];
        }

        return { a, prev };
    }
};

Tree tree;
void solve() {
    int n, q, r;
    cin >> n >> q >> r;
    r--;
    tree.init(n);
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        tree.add_edge(u, v);
    }
    
    tree.build(r);
    int cur_r = r;
    while (q--) {
        char t; int v;
        cin >> t >> v;
        v--;
        if (t == '0') {
            cur_r = v;
        } else {
            auto [lca, prev] = tree.lca_prev(v, cur_r);
            if (v == cur_r) { cout << n << "\n"; }
            else if (lca == v) { cout << n - tree.sz[prev] << "\n"; }
            else { cout << tree.sz[v] << "\n"; }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    for (int i = 1; i <= tc; i++) {
        cout << "Case #" << i << ":\n";
        solve();
    }

    return 0;
}
