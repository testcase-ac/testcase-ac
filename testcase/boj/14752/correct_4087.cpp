#include <bits/stdc++.h>
using namespace std;
const int MX = 1e4+1;
struct info {
    int pos, len;
};
int dp[MX][MX];
info arr[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> arr[i].pos;
    }
    for(int i=0; i<N; i++) {
        cin >> arr[i].len;
    }
    sort(arr, arr+N, [](info a, info b){return a.pos < b.pos;});
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = INT_MIN;
    dp[0][1] = arr[0].pos;
    for(int i=0; i<N; i++) {
        for(int j=0; j<=i+1; j++) {
            //printf("dp %d %d = %d\n", i, j, dp[i][j]);
            if(dp[i][j] + arr[i+1].len < arr[i+1].pos) {
                dp[i+1][j] = min(dp[i+1][j], dp[i][j]+arr[i+1].len);
                dp[i+1][j+1] = min(dp[i+1][j+1], arr[i+1].pos);
            } else if(dp[i][j] <= arr[i+1].pos) {
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + arr[i+1].len);
            } else {
                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + arr[i+1].len);
            }
        }
    }
    int ans = 0;
    for(int i=N; i>=0; i--) {
        if(dp[N-1][i] < 0x3f3f3f3f) {
            return !(cout << N-i);
        }
    }
}
