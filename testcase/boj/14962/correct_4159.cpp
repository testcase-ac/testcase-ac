#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()
const int MX = 2e5;
int dp[3][MX][51], airport[3];
void solve_city(int city) {
    auto cdp = dp[city];
    cdp[0][1] = 0;
    int N, M;
    cin >> N >> M;
    vector<int> hotel(N+1);
    for(int i=1; i<=N; i++) {
        cin >> hotel[i];
    }
    vector<vector<pair<int,int>>> adj(N+1);
    rep(i, M) {
        int u, v, g;
        cin >> u >> v >> g;
        adj[u].push_back({v, g});
    }
    cin >> airport[city];
    for(int t=0; t<MX-1; t++) {
        for(int u=1; u<=N; u++) {
            cdp[t+1][u] = min(cdp[t+1][u], cdp[t][u] + hotel[u]);
            for(auto [v, w]: adj[u]) {
                cdp[t+1][v] = min(cdp[t+1][v], cdp[t][u] + w);
            }
        }
        // if(t < 5) {
        //     printf("at city = %d, t = %d, airport dist = %d\n", city, t, cdp[t][airport[city]]);
        // }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int P;
    cin >> P;
    memset(dp, 0x3f, sizeof dp);
    int ans = dp[0][0][0], inf = dp[0][0][0];
    for(int i=0; i<P; i++) {
        solve_city(i);
    }
    for(int t=0; t<MX; t++) {
        int cur = 0, ok = 1;
        for(int c=0; c<P; c++) {
            if(dp[c][t][airport[c]] >= inf) {
                ok = 0;
            }
            cur += dp[c][t][airport[c]];
        }
        if(ok) {
            ans = min(ans, cur);
        }
    }
    cout << ans;
}
