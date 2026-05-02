#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;

struct Q {
    int l;
    int r;
};

constexpr int MAX_N = 1'000'000;
constexpr int MAX_Q = 1'000'000;

struct Fenwick {
    array<int, MAX_N+1> tree;
    int query(int i) {
        i++;
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
    void add(int i, int x) {
        i++;
        while (i <= MAX_N) {
            tree[i] += x;
            i += i & -i;
        }
    }
};

Fenwick fw;
array<int, MAX_N+1> arr;
array<int, MAX_N> id, last;
array<Q, MAX_Q> ql;
array<int, MAX_Q> qidx, ans;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> stack;
    stack.reserve(n+1);

    // sentinel for simpler code
    stack.push_back(n);
    arr[n] = -1;

    int nid = 0;
    for (int i = 0; i < n; i++) {
        while (arr[stack.back()] > arr[i]) {
            stack.pop_back();
        }
        
        if (arr[stack.back()] == arr[i]) {
            id[i] = id[stack.back()];
        } else {
            id[i] = nid++;
            stack.push_back(i);
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> ql[i].l >> ql[i].r;
        ql[i].l--; ql[i].r--;
    }

    iota(qidx.begin(), qidx.begin()+q, 0);
    sort(qidx.begin(), qidx.begin()+q, [&](int a, int b) {
        return ql[a].r < ql[b].r;
    });

    last.fill(-1);
    int k = 0;
    for (int idx = 0; idx < q; idx++) {
        int i = qidx[idx];
        auto [l, r] = ql[i];

        for (; k <= r; k++) {
            if (last[id[k]] != -1) { fw.add(last[id[k]], -1); }
            last[id[k]] = k;
            fw.add(k, 1);
        }
        k--;

        ans[i] = fw.query(r) - fw.query(l-1);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
