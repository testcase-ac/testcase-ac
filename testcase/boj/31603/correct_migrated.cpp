#include <iostream>
#include <array>
#include <vector>

using namespace std;
using i64 = long long;

struct PersistentSegTree {
    struct Node { int l, r; i64 val; };
    int& left(int i) { return nodes[i].l; }
    int& right(int i) { return nodes[i].r; }
    i64& val(int i) { return nodes[i].val; }

    int n, log2n;
    vector<Node> nodes;
    vector<int> roots;

    int alloc() {
        nodes.push_back({ 0, 0, 0 });
        return nodes.size()-1;
    }

    int init(int sz, int q_resv) {
        this->log2n = 32 - __builtin_clz(sz-1);
        this->n = 1 << log2n;

        nodes.reserve(q_resv*log2n + 10);
        roots.reserve(q_resv + 10);
        roots.push_back(alloc());
        return roots.size()-1;
    }

    i64 update_add(int i, i64 x, int ver_old) {
        int old_r = roots[ver_old];
        int cur_r = alloc();
        roots.push_back(cur_r);

        auto rec = [&](auto&& self, int l, int r, int cur, int old) -> void {
            if (l == r) {
                val(cur) = val(old) + x;
                return;
            }

            int m = (l + r) >> 1;
            if (i <= m) {
                left(cur) = alloc();
                right(cur) = right(old);
                self(self, l, m, left(cur), left(old));
            } else {
                left(cur) = left(old);
                right(cur) = alloc();
                self(self, m+1, r, right(cur), right(old));
            }

            val(cur) = val(left(cur)) + val(right(cur));
        };

        rec(rec, 0, n-1, cur_r, old_r);
        return roots.size()-1;
    }

    i64 query_sum(int l, int r, int ver) {
        auto rec = [&](auto&& self, int nl, int nr, int cur) -> i64 {
            if (cur == -1) { return 0; }
            if (nr < l || r < nl) { return 0; }
            if (l <= nl && nr <= r) { return val(cur); }

            int m = (nl + nr) >> 1;
            return self(self, nl, m, left(cur)) + self(self, m+1, nr, right(cur));
        };

        return rec(rec, 0, n-1, roots[ver]);
    }

    int query_kth_idx(i64 x, int ver_p1, int ver_p2, int ver_n1, int ver_n2) {
        int idx = 0; i64 sum = 0;
        int cur_p1 = roots[ver_p1], cur_p2 = roots[ver_p2], cur_n1 = roots[ver_n1], cur_n2 = roots[ver_n2];
        for (int k = log2n-1; k >= 0; k--) {
            i64 nsum = sum + val(left(cur_p1)) + val(left(cur_p2)) - val(left(cur_n1)) - val(left(cur_n2));
            if (nsum >= x) {
                cur_p1 = left(cur_p1); cur_p2 = left(cur_p2); cur_n1 = left(cur_n1); cur_n2 = left(cur_n2);
            } else {
                cur_p1 = right(cur_p1); cur_p2 = right(cur_p2); cur_n1 = right(cur_n1); cur_n2 = right(cur_n2);
                sum = nsum;
                idx += 1 << k;
            }
        }
        return idx;
    }

    void dump() {
        int ver = 0;
        for (int x : roots) {
            cout << "DUMP! ver=" << ver << ": ";
            for (int i = 0; i < n; i++) {
                cout << query_sum(i, i, ver) << " ";
            }
            cout << endl;
            ver++;
        }
    }
};

struct RootedTree {
    array<vector<int>, 100'000> child;
    array<array<int, 18>, 100'000> par;
    array<int, 100'000> sz, depth, tin, tout;
    int rt, n;

    void init(int n) {
        this->n = n;
    }

    void add_edge(int u, int v) {
        child[u].push_back(v);
        par[v][0] = u;
    }
    void set_root(int rt) {
        this->rt = rt;
        par[rt][0] = rt;
    }

    void build() {
        int t = -1;
        int d = -1;

        auto dfs = [&](auto&& self, int u) -> void {
            d++;
            tin[u] = ++t;
            sz[u] = 1;
            depth[u] = d;
            for (int v : child[u]) {
                self(self, v);
                sz[u] += sz[v];
            }
            tout[u] = t;
            d--;
        };

        dfs(dfs, rt);

        for (int i = 1; i <= 17; i++) {
            for (int v = 0; v < n; v++) {
                par[v][i] = par[par[v][i-1]][i-1];
            }
        }
    }

    int up(int v, int x) {
        for (int i = 0; i <= 17; i++) {
            if ((1 << i) & x) {
                v = par[v][i];
            }
        }
        return v;
    }
};

PersistentSegTree pst_lca, pst_kth;
RootedTree tree;
array<int, 100'000> inv_tin, ver_lca;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    tree.init(n);
    for (int v = 0; v < n; v++) {
        int u;
        cin >> u;
        u--;
        if (u == -1) { tree.set_root(v); continue; }
        tree.add_edge(u, v);
    }
    
    tree.build();
    for (int v = 0; v < n; v++) { inv_tin[tree.tin[v]] = v; }

    pst_lca.init(n, 2*n);
    
    int rt = tree.rt;
    ver_lca[rt] = pst_lca.update_add(rt, tree.sz[rt], 0);
    for (int t = 1; t < n; t++) {
        int v = inv_tin[t];
        int p = tree.par[v][0];

        int upd_ver = pst_lca.update_add(p, -tree.sz[v], ver_lca[p]); // if LCA(u, v) = p, u and v cannot be in the same subtree under p
        ver_lca[v] = pst_lca.update_add(v, tree.sz[v], upd_ver); // if LCA(u, v) = v, u is under v's subtree
    }


    pst_kth.init(n, n);
    for (int t = 0; t < n; t++) {
        pst_kth.update_add(inv_tin[t], 1, t);
    }

    while (q--) {
        i64 k;
        cin >> k;
        k--;

        int v = k/n; k %= n;
        int lca = pst_lca.query_kth_idx(k+1, ver_lca[v], 0, 0, 0);
        int cnt = pst_lca.query_sum(0, lca-1, ver_lca[v]);

        int tin_sublca = 0, tout_sublca = -1;
        if (lca != v) {
            int sublca = tree.up(v, tree.depth[v] - tree.depth[lca] - 1);
            tin_sublca = tree.tin[sublca]; tout_sublca = tree.tout[sublca];
        }

        int a = v;
        int b = lca;
        int c = pst_kth.query_kth_idx(k-cnt+1, tree.tout[lca]+1, tin_sublca, tree.tin[lca], tout_sublca+1);

        cout << i64(a)*n*n + i64(b)*n + i64(c) << "\n";
    }

    return 0;
}
