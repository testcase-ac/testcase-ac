#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e6;
int d[MX];
int N, Q;
struct elem {
    int i, dp, h;
};
int solve(int K) {
    deque<elem> dq;
    for(int i = 0; i < N; i++) {
        while(dq.size() && dq.front().i < i - K) dq.pop_front();
        int dp = dq.size() ? (dq.front().dp + (dq.front().h <= d[i] ? 1 : 0)) : 0;
        while(dq.size() && (dq.back().dp > dp || (dq.back().dp == dp && dq.back().h < d[i])))
            dq.pop_back();
        dq.push_back({i, dp, d[i]});
    }
    return dq.back().dp;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> d[i];
    }
    cin >> Q;
    for(int i = 0; i < Q; i++) {
        int k;
        cin >> k;
        cout << solve(k) << '\n';
    }
}
