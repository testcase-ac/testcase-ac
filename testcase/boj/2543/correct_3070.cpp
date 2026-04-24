#include <bits/stdc++.h>
using namespace std;
#define int long long
struct elem {
    int l, r;
    bool operator<(const elem &o) const {
        return r < o.r;
    }
};
const int MOD = 20070713;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<elem> v(N);
    vector<int> dp(N);
    for(int i = 0; i < N; i++) {
        cin >> v[i].l >> v[i].r;
    }
    sort(v.begin(), v.end());
    auto get_dp = [&](int i) {
        return i < 0 ? 1 : dp[i];
    };
    for(int i = 0; i < N; i++) {
        int t = lower_bound(v.begin(), v.end(), elem{0, v[i].l}) - v.begin();
        dp[i] = (get_dp(i - 1) + get_dp(t - 1)) % MOD;
    }
    cout << dp[N - 1] << '\n';
}
