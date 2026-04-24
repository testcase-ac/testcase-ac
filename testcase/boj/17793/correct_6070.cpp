#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5000;
int N, K;
long double P;
long double dp[MX][51], die_at[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> K >> P;
    dp[0][0] = 1;
    long double ans = 0;
    for(int i=1; i<MX; i++) {
        for(int j=0; j<=K; j++) {
            if(j < K)
                dp[i][j] = dp[i-1][j] * P;
            else
                dp[i][j] = dp[i-1][j];
            if(j) 
                dp[i][j] += dp[i-1][j-1] * (1 - P);
        }
        // a: ended before time i / b: ended at time i / ab: sum of a and b
        long double pa = dp[i-1][K], pb = dp[i][K] - dp[i-1][K], pab = dp[i][K];
        ans += pow(pab, N) - pow(pa, N) - pow(pa, N-1) * pb * N;
    }
    cout << fixed << setprecision(9) << ans << '\n';
}
