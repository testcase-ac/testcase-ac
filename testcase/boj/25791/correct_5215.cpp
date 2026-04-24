#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[5001][3], dp[5001][5001];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int L, T;
    cin >> L >> T;
    for(int i=1; i<=T; i++) {
        for(int j=0; j<3; j++) {
            cin >> arr[i][j];
        }
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for(int i=1; i<=T; i++) {
        for(int j=0; j<=min(i*3, L); j++) {
            dp[i][j] = dp[i-1][j];
            if(j >= 1) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1] + arr[i][0]);
            }
            if(j >= 2) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-2] + arr[i][1]); 
            }
            if(j >= 3) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-3] + arr[i][2]); 
            }
        }
    }
    cout << dp[T][L];
}
