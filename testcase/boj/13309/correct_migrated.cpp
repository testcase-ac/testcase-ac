#include <iostream>
#include <array>
#include <vector>
#include <cassert>
#include <bitset>

using namespace std;

struct SegTreeBitset {
    static constexpr int LEAF = 262144;
    bitset<2*LEAF> tree;

    void init() {
        tree.reset();
    }

    void update_set(int i) {
        i += LEAF;
        tree.set(i);
        i >>= 1;
        while (i >= 1) {
            tree.set(i);
            i >>= 1;
        }
    }

    bool query_true(int l, int r) {
        l += LEAF; r += LEAF;
        while (l <= r) {
            if (l & 1) { if (tree.test(l++)) { return true; } }
            if (!(r & 1)) { if (tree.test(r--)) { return true; } }
            l >>= 1; r >>= 1;
        }
        return false;
    }
};

struct HLDTree {
    SegTreeBitset seg;
    array<vector<int>, 200'000> adj;
    int n;

    void init(int n) {
        this->n = n;
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    array<int, 200'000> sz, depth, par, heavy, head, tin;
    void build() {
        auto fill_info = [&](auto self, int u, int p) -> void {
            depth[u] = depth[p] + 1;
            heavy[u] = -1;
            sz[u] = 1;
            par[u] = p;
            for (int v : adj[u]) {
                self(self, v, u);
                sz[u] += sz[v];
                if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) { heavy[u] = v; }
            }
        };
        fill_info(fill_info, 0, 0);

        int t = -1;
        auto decomp = [&](auto self, int u, int p) -> void {
            tin[u] = ++t;

            if (heavy[u] == -1) { return; }
            head[heavy[u]] = head[u];
            self(self, heavy[u], u);

            for (int v : adj[u]) {
                if (v == heavy[u]) { continue; }
                head[v] = v;
                self(self, v, u);
            }
        };
        head[0] = 0;
        decomp(decomp, 0, 0);

        seg.init();
    }

    bool query_true(int u, int v) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) { swap(u, v); }
            if (seg.query_true(tin[head[u]], tin[u])) { return true; }
            u = par[head[u]];
        }
        if (depth[u] < depth[v]) { swap(u, v); }
        return seg.query_true(tin[v]+1, tin[u]);
    }

    void update_set(int v) {
        seg.update_set(tin[v]);
    }
};

HLDTree hld;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    hld.init(n);
    for (int v = 1; v < n; v++) {
        int u;
        cin >> u;
        u--;
        hld.add_edge(u, v);
    }
    hld.build();

    while (q--) {
        int b, c, d;
        cin >> b >> c >> d;
        b--; c--;
        if (d == 0) {
            cout << (hld.query_true(b, c) ? "NO\n" : "YES\n");
        } else if (d == 1) {
            if (hld.query_true(b, c)) {
                cout << "NO\n";
                hld.update_set(c);
            } else {
                cout << "YES\n";
                hld.update_set(b);
            }
        } else { assert(false); }
    }

    return 0;
}
