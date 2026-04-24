#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()
const int MOD = 1e9+7;
int p2[3003];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    p2[0] = 1;
    for(int i=1; i<=N; i++) {
        p2[i] = (p2[i-1] * 2) % MOD;
    }
    vector<int> v(N);
    for(int &t: v) cin >> t;
    int ans = 0;
    for(int i=0; i<N; i++) {
        for(int j=i+1; j<N; j++) {
            int d = v[j] - v[i];
            auto itl = lower_bound(all(v), v[i]-d), itr = lower_bound(all(v), v[j]+d);
            int cnt = N - (itr - itl);
            ans += p2[cnt];
        }
    }
    ans %= MOD;
    cout << ans;
}
