#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 123456789, MX = 1e6 + 5;
int dp[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int L, S;
    cin >> L >> S;
    dp[0] = 1;
    int acc = 1;
    for(int i=1; i<L; i++) {
        dp[i] = acc;
        acc += dp[i];
        if(i >= S) {
            acc -= dp[i-S];
        }
        acc = (acc + MOD) % MOD;
    }
    int ans = 0;
    for(int i=0; i<S; i++) {
        ans += dp[L-1-i] * (i+1);
        ans %= MOD;
    }
    cout << ans;
}
