#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <span>

using namespace std;
using i64 = long long;

constexpr i64 INF = 123456789123456789;

struct LazySegTree {
    struct MinCnt { i64 val; int cnt; };
    static constexpr MinCnt merge(const MinCnt& a, const MinCnt& b) {
        if (a.val < b.val) { return a; }
        else if (a.val > b.val) { return b; }
        else { return { a.val, a.cnt + b.cnt }; }
    }

    static constexpr MinCnt I = { INF, 0 };

    int n, h, leaf;
    vector<MinCnt> tree;
    vector<int> lazy;

    void reset() {
        tree.clear();
        lazy.clear();
    }

    void init(int n) {
        this->n = n;
        this->h = 32 - __builtin_clz(n-1);
        this->leaf = 1 << h;
        
        tree.resize(2*leaf, I);
        lazy.resize(leaf, 0);
    }

    span<MinCnt> leaves() { return { tree.data()+leaf, leaf }; }

    void build() {
        for (int i = leaf-1; i >= 1; i--) { pull(i); }
    }

    void apply(int i, i64 x) {
        tree[i].val += x;
        if (i < leaf) { lazy[i] += x; }
    }

    void push(int i) {
        apply(2*i, lazy[i]);
        apply(2*i+1, lazy[i]);
        lazy[i] = 0;
    }

    void pull(int i) {
        tree[i] = merge(tree[2*i], tree[2*i+1]);
    }

    void push_lr(int l, int r) {
        for (int k = h; k >= 1; k--) {
            int mask = (1 << k) - 1;
            if (l & mask) { push(l >> k); }
            if ((r+1) & mask) { push(r >> k); }
        }
    }
    void pull_lr(int l, int r) {
        for (int k = 1; k <= h; k++) {
            int mask = (1 << k) - 1;
            if (l & mask) { pull(l >> k); }
            if ((r+1) & mask) { pull(r >> k); }
        }
    }

    void update_add(int l, int r, int x) {
        l += leaf; r += leaf;
        push_lr(l, r);

        int tl = l, tr = r;
        while (tl <= tr) {
            if (tl & 1) { apply(tl++, x); }
            if (~tr & 1) { apply(tr--, x); }
            tl >>= 1; tr >>= 1;
        }

        pull_lr(l, r);
    }

    MinCnt query_min() { return tree[1]; }
};

struct Update { int i, l, r, x; };

LazySegTree seg;
array<Update, 400'000> upd;
array<int, 400'000> ys;
unordered_map<int, int> comp;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;

        ys[2*i] = y1;
        ys[2*i+1] = y2;

        upd[2*i] = { x1, y1, y2, 1 };
        upd[2*i+1] = { x2, y1, y2, -1 };
    }

    sort(ys.begin(), ys.begin()+2*n);
    int u = unique(ys.begin(), ys.begin()+2*n) - ys.begin();
    for (int i = 0; i < u; i++) { comp[ys[i]] = i; }
    for (int i = 0; i < 2*n; i++) {
        upd[i].l = comp[upd[i].l];
        upd[i].r = comp[upd[i].r]-1;
    }

    sort(upd.begin(), upd.begin()+2*n, [&](const auto& a, const auto& b) { return a.i < b.i; });

    seg.init(u);
    auto leaves = seg.leaves();
    for (int i = 0; i < u-1; i++) {
        leaves[i] = { 0, ys[i+1] - ys[i] };
    }
    seg.build();
    
    i64 res = 0;
    i64 i0 = -1;
    for (int k = 0; k < 2*n; k++){
        i64 i = upd[k].i;
        auto [val, cnt] = seg.query_min();
        res += (ys[u-1] - ys[0])*(i - i0);
        if (val == 0) { res -= cnt*(i - i0); }
        i0 = i;
        seg.update_add(upd[k].l, upd[k].r, upd[k].x);
    }

    cout << res << endl;

    return 0;
}
