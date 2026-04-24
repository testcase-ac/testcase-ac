#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[1000][1000], dp[1000][1000];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C;
    cin >> R >> C;
    for(int r=0; r<R; r++) {
        for(int c=0; c<C; c++) {
            cin >> arr[r][c];
        }
    }
    memset(dp, 0x3f, sizeof dp);
    for(int r=0; r<R; r++) {
        if(arr[r][0] == 0)
            dp[r][0] = 0;
    }
    for(int c=1; c<C; c++) {
        for(int r=0; r<R; r++) {
            if(arr[r][c] == 0)
                dp[r][c] = dp[r][c-1];
        }
        for(int r=1; r<R; r++) {
            if(arr[r][c] == 0)
                dp[r][c] = min(dp[r][c], dp[r-1][c]+1);
        }
        for(int r=R-2; r>=0; r--) {
            if(arr[r][c] == 0) {
                dp[r][c] = min(dp[r][c], dp[r+1][c] + 1);
            }
        }
    }
    // for(int r=0; r<R; r++) {
    //     for(int c=0; c<C; c++) {
    //         cout << dp[r][c];
    //     }
    //     cout << '\n';
    // }
    int ans = INT_MAX;
    for(int r=0; r<R; r++) {
        ans = min(ans, dp[r][C-1]);
    }
    if(ans == INT_MAX) {
        return !(cout << "NIE");
    }
    cout << ans;
}
