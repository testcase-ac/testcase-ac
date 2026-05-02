#include <iostream>
#include <array>
#include <algorithm>
#include <utility>
#include <span>

using namespace std;
using i64 = long long;

constexpr i64 INF = 1ll << 60;

struct MaxSubarrSegTree {
    struct Val { i64 sum, suff_max; };
    Val merge(const Val& a, const Val& b) const {
        return {
            a.sum + b.sum,
            max(a.suff_max + b.sum, b.suff_max)
        };
    }
    
    static constexpr int LEAF = 1 << 20;
    array<Val, 2*LEAF> tree;
    
    int leaf;
    void init(int n) {
        this->leaf = 1 << (32 - __builtin_clz(n-1));
    }
    span<Val> leaves() { return { tree.data()+leaf, leaf }; }
    void build() {
        for (int i = leaf-1; i >= 0; i--) {
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }

    void update_add(int i, i64 x) {
        i += leaf;
        tree[i].sum += x; tree[i].suff_max += x;
        i >>= 1;
        while (i >= 1) {
            tree[i] = merge(tree[2*i], tree[2*i+1]);
            i >>= 1;
        }
    }

    Val query(int l, int r) {
        l += leaf; r += leaf;
        Val l_res = { 0, -INF };
        Val r_res = { 0, -INF };
        while (l <= r) {
            if (l & 1) { l_res = merge(l_res, tree[l++]); }
            if (~r & 1) { r_res = merge(tree[r--], r_res); }
            l >>= 1; r >>= 1;
        }
        return merge(l_res, r_res);
    }
};

MaxSubarrSegTree seg;
array<pair<int, int>, 1'000'000> upd;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    seg.init(1'000'001);
    auto leaves = seg.leaves();
    fill(leaves.begin(), leaves.end(), MaxSubarrSegTree::Val { -1, -1 });
    seg.build();

    int q;
    cin >> q;
    for (int qi = 0; qi < q; qi++) {
        char t;
        cin >> t;
        if (t == '+') {
            int t, d;
            cin >> t >> d;
            seg.update_add(t, d);
            upd[qi] = { t, d };
        } else if (t == '-') {
            int i;
            cin >> i;
            i--;
            seg.update_add(upd[i].first, -upd[i].second);
        } else if (t == '?') {
            int t;
            cin >> t;
            cout << 1 + seg.query(0, t).suff_max << "\n";
        }
    }

    return 0;
}
