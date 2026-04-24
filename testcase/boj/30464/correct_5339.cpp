#include <bits/stdc++.h>
using namespace std;
const int MX = 2e5+5;
int arr[MX], dp[3][MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=1; i<=N; i++) {
        cin >> arr[i];
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0][N] = dp[1][N] = dp[2][N] = 0;
    const int INF = 0x3f3f3f3f;
    for(int i=N-1; i>=1; i--) {
        int t = i+arr[i];
        if(t <= N) {
            dp[0][i] = dp[0][t] + 1;
        }
    }
    for(int i=1; i<N; i++) {
        dp[1][i] = dp[0][i];
        int t = i-arr[i];
        if(t >= 1 && dp[1][t] < INF)
            if(dp[1][i] >= INF) {
                dp[1][i] = dp[1][t] + 1;
            } else {
                dp[1][i] = max(dp[1][i], dp[1][t] + 1);
            }
    }
    for(int i=N-1; i>=1; i--) {
        dp[2][i] = dp[1][i];
        int t = i+arr[i];
        if(t < N && dp[2][t] < INF) {
            if(dp[2][i] >= INF) {
                dp[2][i] = dp[2][t] + 1;
            } else {
                dp[2][i] = max(dp[2][i], dp[2][t] + 1);
            }
        }
    }
    if(dp[2][1] >= INF) {
        cout << -1;
    } else {
        cout << dp[2][1];
    }
}
