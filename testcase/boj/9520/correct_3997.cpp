#include <bits/stdc++.h>
using namespace std;
const int MX = 1501;
int cost[MX][MX], dp[MX][MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> cost[i][j];
        }
    }
    memset(dp, 0x3f, sizeof dp);
    dp[1][1] = 0;
    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= i; j++) {
            dp[i + 1][j] = min({dp[i + 1][j], dp[i][j] + cost[i + 1][i], dp[i][j] + cost[i][i + 1]});
            dp[i + 1][i] = min({dp[i + 1][i], dp[i][j] + cost[j][i + 1], dp[i][j] + cost[i + 1][j]});
        }
    }
    int ans = INT_MAX;
    for(int i = 1; i <= n; i++) {
        ans = min({ans, dp[n][i], dp[i][n]});
    }
    cout << ans;
}
