#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
int N, K;
int dp[1001][1001], arr[1001];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> K;
    map<int, int> mp;
    for(int i=1; i<=N; i++) {
        int t;
        cin >> t;
        mp[t]++;
    }
    int t = 1;
    for(auto [a, b]: mp) {
        arr[t++] = b;
    }
    N = t;
    for(int i=0; i<=N; i++) {
        dp[i][0] = 1;
    }
    for(int j=1; j<=K; j++) {
        for(int i=j; i<=N; i++) {
            dp[i][j] = (dp[i-1][j-1] * arr[i] + dp[i-1][j]) % MOD;
            //printf("dp %d %d = %d\n", i, j, dp[i][j]);
        }
    }
    cout << dp[N][K];
}
