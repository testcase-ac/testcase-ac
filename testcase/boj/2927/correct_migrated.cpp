#include <iostream>
#include <array>
#include <vector>
#include <span>
#include <numeric>
#include <string>

using namespace std;

constexpr int MAX_N = 30'000;
constexpr int MAX_Q = 300'000;

struct FenwickTree {
    array<int, MAX_N> arr;
    array<int, MAX_N+1> tree;
    int n;

    void init(int n) {
        this->n = n;
    }

    span<int> leaves() { return { arr.begin(), n }; }
    void construct() {
        copy(arr.begin(), arr.begin()+n, tree.begin()+1);
        for (int i = 1; i <= n; i++) {
            int ni = i + (i & -i);
            if (ni <= n) { tree[ni] += tree[i]; }
        }
    }

    int query_psum(int i) {
        i++;
        int res = 0;
        while (i >= 1) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }

    int query_sum(int a, int b) {
        return query_psum(b) - query_psum(a-1);
    }

    void update_add(int i, int x) {
        i++;
        while (i <= n) {
            tree[i] += x;
            i += i & -i;
        }
    }
};

struct NodeHLDTree {
    FenwickTree fw;
    array<vector<int>, MAX_N> adj;
    array<int, MAX_N> weight;
    int n;

    void init(int n) {
        this->n = n;
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void set_weight(int v, int w) { weight[v] = w; }

    array<int, MAX_N> par, size, depth, heavy, segid, head, root;
    void construct() {
        auto fill_info = [&](auto self, int u, int p) -> void {
            root[u] = root[p];
            par[u] = p;
            depth[u] = depth[p]+1;
            size[u] = 1;
            heavy[u] = -1;
            for (int v : adj[u]) {
                if (v == p) { continue; }
                self(self, v, u);
                size[u] += size[v];
                if (heavy[u] == -1 || size[v] > size[heavy[u]]) { heavy[u] = v; }
            }
        };

        for (int i = 0; i < n; i++) {
            if (depth[i] != 0) { continue; }
            root[i] = i;
            depth[i] = -1;
            fill_info(fill_info, i, i);
        }

        int nid = 0, cur_head = -1;
        auto decompose = [&](auto self, int u, int p) -> void {
            segid[u] = nid++;

            if (cur_head == -1) { cur_head = u; }
            head[u] = cur_head;

            if (heavy[u] == -1) {
                cur_head = -1;
                return;
            }
            self(self, heavy[u], u);

            for (int v : adj[u]) {
                if (v == p || v == heavy[u]) { continue; }
                self(self, v, u);
            }
        };

        for (int i = 0; i < n; i++) {
            if (root[i] != i) { continue; }
            decompose(decompose, i, i);
        }

        fw.init(n);
        auto arr = fw.leaves();
        for (int v = 0; v < n; v++) { arr[segid[v]] = weight[v]; }
        fw.construct();
    }

    int query_sum(int a, int b) {
        if (root[a] != root[b]) { return 0; }
        int res = 0;
        while (head[a] != head[b]) {
            if (depth[head[a]] > depth[head[b]]) { swap(a, b); }
            res += fw.query_sum(segid[head[b]], segid[b]);
            b = par[head[b]];
        }
        if (depth[a] > depth[b]) { swap(a, b); }
        res += fw.query_sum(segid[a], segid[b]);
        return res;
    }

    void update(int v, int x) {
        fw.update_add(segid[v], x - weight[v]);
        weight[v] = x;
    }
};

using u8 = unsigned char;

struct UnionFind {
    array<int, MAX_N> par;
    array<u8, MAX_N> rank;
    int n;

    void init(int n) {
        this->n = n;
        iota(par.begin(), par.begin()+n, 0);
        fill(rank.begin(), rank.begin()+n, 0);
    }

    int find(int x) {
        if (x == par[x]) { return x; }
        par[x] = find(par[x]);
        return par[x];
    }

    bool union_(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) { return false; }
        if (rank[a] < rank[b]) { swap(a, b); }
        par[b] = a;
        if (rank[a] == rank[b]) { rank[a]++; }
        return true;
    }
};

struct Query {
    char t;
    int a, b;
};

array<Query, MAX_Q> qarr;
array<string, MAX_Q> qans;
NodeHLDTree hld;
UnionFind uf;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    hld.init(n);
    
    for (int i = 0; i < n; i++) {
        int w;
        cin >> w;
        hld.set_weight(i, w);
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        auto& [t, a, b] = qarr[i];
        cin >> t;
        for (int ch = cin.get(); !isspace(ch); ch = cin.get()) {}
        cin >> a >> b;
    }

    uf.init(n);
    for (int i = 0; i < q; i++) {
        auto [t, a, b] = qarr[i];
        if (t != 'b') { continue; }
        a--; b--;

        if (!uf.union_(a, b)) {
            qans[i] = "no\n";
            continue;
        }
        hld.add_edge(a, b);
        qans[i] = "yes\n";
    }

    hld.construct();

    uf.init(n);
    for (int i = 0; i < q; i++) {
        auto [t, a, b] = qarr[i];
        if (t == 'b') {
            a--; b--;
            uf.union_(a, b);
        } else if (t == 'p') {
            a--;
            hld.update(a, b);
        } else if (t == 'e') {
            a--; b--;
            if (uf.find(a) != uf.find(b)) {
                qans[i] = "impossible\n";
            } else {
                qans[i] = to_string(hld.query_sum(a, b));
                qans[i].push_back('\n');
            }
        }
    }

    for (int i = 0; i < q; i++) {
        cout << qans[i];
    }

    return 0;
}
