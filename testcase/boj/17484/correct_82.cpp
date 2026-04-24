#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[6][6][3], R, C, arr[6][6];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> R >> C;
    for(int r=0; r<R; r++) {
        for(int c=0; c<C; c++) {
            cin >> arr[r][c];
        }
    }
    memset(dp, 0x3f, sizeof dp);
    for(int c=0; c<C; c++) {
        for(int d=0; d<3; d++) {
            dp[0][c][d] = arr[0][c];
        }
    }
    for(int r=1; r<R; r++) {
        for(int c=0; c<C; c++) {
            for(int d=0; d<3; d++) {
                for(int pd=0; pd<3; pd++) {
                    if(pd == d) continue;
                    int pc = c - (pd - 1);
                    if(pc < 0 || pc >= C) continue;
                    dp[r][c][d] = min(dp[r][c][d], dp[r-1][pc][pd] + arr[r][c]);
                }
            }
        }
    }
    int ans = INT_MAX;
    for(int c=0; c<C; c++) {
        for(int d=0; d<3; d++) {
            ans = min(ans, dp[R-1][c][d]);
        }
    }
    cout << ans;
}
