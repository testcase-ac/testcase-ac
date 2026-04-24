#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 401;
int N, A[MX][MX], B[MX][MX], dp[MX][MX][MX];
int solve() {
    memset(dp, 0, sizeof dp);
    dp[1][1][2] = A[2][1] + B[1][2];
    for(int c=1; c<N; c++) {
        for(int r1=1; r1<N; r1++) {
            for(int r2=r1+1; r2<=N; r2++) {
                auto &val = dp[c][r1][r2];
                if(r1 > 1)
                    val = max(val, dp[c][r1-1][r2] + A[c+1][r1]);
                val = max(val, dp[c][r1][r2-1] + B[c][r2]);
                if(c > 1 && r1 < r2)
                    val = max(val, dp[c-1][r1][r2] + A[c+1][r1] + B[c][r2]);
            }
        }
    }
    return dp[N-1][N-1][N];
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            cin >> A[i][j];
        }
    }
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            cin >> B[i][j];
        }
    }
    int ans = solve();
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            swap(A[i][j], B[i][j]);
        }
    }
    ans = max(ans, solve());
    cout << ans;


}
