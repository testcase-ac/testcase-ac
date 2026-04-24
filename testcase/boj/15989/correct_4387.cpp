#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 10001;

int dp[MX];
/*
1만 사용할 수 있을 때: 모든 dp값에 대해 dp[i] = 1
2도 사용할 수 있을 때: dp[i] = dp[i-2] + dp[i-4] + dp[i-6] + ...
3도 사용할 수 있을 때: dp[i] = dp[i-3] + dp[i-6] + dp[i-9] + ...
*/
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    // 1만 사용할 수 있을 때
    for(int i=0; i<=MX; i++) {
        dp[i] = 1;
    }
    // 2도 사용할 수 있을 때
    for(int i=MX-1; i>=0; i--) {
        for(int j=2; j<=i; j+=2) {
            dp[i] += dp[i-j];
        }
    }
    // 3도 사용할 수 있을 때
    for(int i=MX-1; i>=0; i--) {
        for(int j=3; j<=i; j+=3) {
            dp[i] += dp[i-j];
        }
    }
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        cout << dp[N] << '\n';
    }
}
