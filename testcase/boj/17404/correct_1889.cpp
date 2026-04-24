#include <bits/stdc++.h>
using namespace std;
int dp[1000][3][3];
int cost[1000][3];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
        for(int j=0; j<3; j++) {
            cin >> cost[i][j];
        }
    }
    memset(dp, 0x3f, sizeof dp);
    for(int i=0; i<3; i++) {
        dp[0][i][i] = cost[0][i];
    }
    for(int i=1; i<N; i++) {
        for(int f=0; f<3; f++) {
            for(int j=0; j<3; j++) {
                for(int k=0; k<3; k++) {
                    if(j == k) continue;
                    dp[i][f][j] = min(dp[i][f][j], dp[i-1][f][k] + cost[i][j]);
                }
            }
        }
    }
    int ans = INT_MAX;
    for(int j=0; j<3; j++) {
        for(int k=0; k<3; k++) {
            if(j == k) continue;
            ans = min(ans, dp[N-1][j][k]);
        }
    }
    cout << ans;
}
