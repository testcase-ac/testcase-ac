#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5 + 1;
int arr[MX], acc[MX];
struct node {
    int val, idx;

    bool operator<(node const& o) const {
        return idx < o.idx;
    }
};
int sum(int l, int r) {
    return acc[r] - acc[l - 1];
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, S;
    cin >> N >> S;
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
        acc[i] = acc[i - 1] + arr[i];
    }
    vector<node> nodes;
    for(int i = 1; i < N; i++) {
        int l = 0, r = min(i, N - i);
        while(l < r) {
            int m = (l + r + 1) / 2;
            if(sum(i - m + 1, i) > S || sum(i + 1, i + m) > S) {
                r = m - 1;
            } else {
                l = m;
            }
        }
        nodes.push_back({l - i, i});
    }
    sort(nodes.begin(), nodes.end(), [](node const& l, node const& r) {
        return l.val < r.val;
    });
    int mx_idx = 0;
    for(int i = 1; i < N; i++) {
        while(nodes.size() && nodes.back().val >= (1 - i)) {
            mx_idx = max(mx_idx, nodes.back().idx);
            nodes.pop_back();
        }
        cout << max((mx_idx - i + 1) * 2, 0ll) << '\n';
    }
    cout << "0\n";
}
