#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
int dp[300][1<<18];
int main() {
    int n, m;
    cin >> n >> m;
    if(n > m) swap(n, m);
    const int all = (1<<(n+1)) - 1;
    dp[0][0] = dp[0][1<<n] = 1;
    for(int i=1; i<n*m; i++) {
        for(int j=0; j<=all; j++) {
            int m1 = (j<<1)&all, m2 = m1|1;
            dp[i][j] = dp[i-1][m1];
            if(!(i%n && j&(1<<n) && m2&(1<<n) && m2&(1<<1))) {
                dp[i][j] += dp[i-1][m2];
                dp[i][j] %= MOD;
            }
        }
    }
    cout << accumulate(dp[n*m-1], dp[n*m-1]+(1<<18), 0LL) % MOD;
}
