#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[1000][1003][8], arr[1000][3];
void mx(int& t, int v) {
    if(t < v) t = v;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(dp, 0xbf, sizeof(dp));
    int n, K;
    cin >> n >> K;
    for(int i = 0; i < n; i++) {
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }

    dp[0][1][3] = arr[0][0] + arr[0][1];
    dp[0][1][6] = arr[0][1] + arr[0][2];
    dp[0][0][0] = 0;
    for(int i = 1; i < n; i++) {
        for(int k = 0; k <= K; k++) {
            for(int bm = 0; bm < 8; bm++) {
                if(!(bm & 1)) {
                    mx(dp[i][k + 1][1], dp[i - 1][k][bm] + arr[i - 1][0] + arr[i][0]);
                    mx(dp[i][k + 2][7], dp[i - 1][k][bm] + arr[i - 1][0] + arr[i][0] + arr[i][1] + arr[i][2]);
                }
                if(!(bm & 2)) {
                    mx(dp[i][k + 1][2], dp[i - 1][k][bm] + arr[i - 1][1] + arr[i][1]);
                }
                if(!(bm & 4)) {
                    mx(dp[i][k + 1][4], dp[i - 1][k][bm] + arr[i - 1][2] + arr[i][2]);
                    mx(dp[i][k + 2][7], dp[i - 1][k][bm] + arr[i - 1][2] + arr[i][2] + arr[i][1] + arr[i][0]);
                }
                if(!(bm & 3)) {
                    mx(dp[i][k + 2][3], dp[i - 1][k][bm] + arr[i][0] + arr[i][1] + arr[i - 1][0] + arr[i - 1][1]);
                }
                if(!(bm & 5)) {
                    mx(dp[i][k + 2][5], dp[i - 1][k][bm] + arr[i][0] + arr[i][2] + arr[i - 1][0] + arr[i - 1][2]);
                }
                if(!(bm & 6)) {
                    mx(dp[i][k + 2][6], dp[i - 1][k][bm] + arr[i - 1][1] + arr[i - 1][2] + arr[i][1] + arr[i][2]);
                }
                mx(dp[i][k][0], dp[i - 1][k][bm]);
                mx(dp[i][k + 1][3], dp[i - 1][k][bm] + arr[i][0] + arr[i][1]);
                mx(dp[i][k + 1][6], dp[i - 1][k][bm] + arr[i][1] + arr[i][2]);
            }
        }
    }
    int ans = -1e15;
    for(int bm = 0; bm < 8; bm++) {
        ans = max(ans, dp[n - 1][K][bm]);
    }

    cout << ans;
}
