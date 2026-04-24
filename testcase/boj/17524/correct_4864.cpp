#include <bits/stdc++.h>
using namespace std;
int t_buk[101];
struct info {
    int t, w;
    bool operator<(const info& o) const {
        return t < o.t;
    }
};
int solve(vector<info> v, int k) {
    if(!v.size()) return 0;
    sort(v.begin(), v.end());
    if(k == 1) {
        int ret = 0;
        for(auto &t: v) {
            ret = max(ret, 30  + (t.t - v[0].t) * t.w);
        }
        return ret;
    }
    int first_t = v[0].t;
    sort(v.begin(), v.end(), [&](const info& a, const info& b) {
        return a.w * (a.t - first_t)  < b.w * (b.t - first_t);
    });
    int ret = INT_MAX;
    for(int i=0; i<v.size(); i++) {
        ret = min(ret, 30 + v[i].w * (v[i].t - first_t) + solve(vector<info>(v.begin() + i + 1, v.end()), k - 1));
    }
    return ret;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    for(int i=0; i<n; i++) {
        int t, w;
        cin >> t >> w;
        t_buk[t] = max(t_buk[t], w);
    }
    vector<info> v;
    for(int i=40; i<=100; i++) {
        if(t_buk[i]) {
            v.push_back({i, t_buk[i]});
        }
    }
    cout << solve(v, k) << '\n';
}
