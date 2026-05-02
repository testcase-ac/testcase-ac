#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <utility>
#include <bitset>
#include <tuple>

using namespace std;
using i64 = long long;

struct Bar { int x, y; };

array<Bar, 300'000> bars;
array<int, 300'000> lchild, rchild, len;
bitset<300'000> done;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    n >>= 1;
    for (int i = 0; i < n; i++) {
        cin >> bars[i].x >> bars[i].y;
        { int _; cin >> _ >> _; }
    }

    int k;
    cin >> k;

    vector<int> st;
    st.reserve(n);
    
    fill(lchild.begin(), lchild.begin()+n, -1);
    fill(rchild.begin(), rchild.begin()+n, -1);
    for (int i = 0; i < n; i++) {
        while (!st.empty() && bars[st.back()].y >= bars[i].y) {
            lchild[i] = st.back();
            st.pop_back();
        }
        if (!st.empty()) { rchild[st.back()] = i; }
        st.push_back(i);
    }

    priority_queue<pair<i64, int>> pq;
    auto dnc = [&](auto&& self, int u, int p) -> pair<i64, int> {
        pair<i64, int> res = { 0, u }; // (drainage, leaf index)
        int l = lchild[u], r = rchild[u];
        len[u] = (u == 0) ? 0 : (bars[u].x - bars[u-1].x);
        if (l != -1) {
            res = max(res, self(self, l, u));
            len[u] += len[l];
        }
        if (r != -1) {
            res = max(res, self(self, r, u));
            len[u] += len[r];
        }
        res.first += i64(len[u])*i64(bars[u].y - bars[p].y);
        pq.push(res);
        return res;
    };

    dnc(dnc, 0, 0); // 0 is always the root

    i64 res = 0;
    for (int _i = 0; _i < k; _i++) {
        auto [val, leaf] = pq.top(); pq.pop();
        while (!pq.empty() && done.test(leaf)) {
            tie(val, leaf) = pq.top(); pq.pop();
        }
        if (pq.empty()) { break; }
        res += val;
        done.set(leaf);
    }

    cout << res << "\n";

    return 0;
}
