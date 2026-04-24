#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MX = 1e5+1;
const ll MOD = 1e9+9;
ll dp[4][MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	dp[1][1] = dp[2][2] = dp[1][3] = dp[2][3] = dp[3][3] = 1;
	for(int t=4; t<MX; t++) {
		dp[1][t] = (dp[2][t-1] + dp[3][t-1]) % MOD;
		dp[2][t] = (dp[1][t-2] + dp[3][t-2]) % MOD;
		dp[3][t] = (dp[1][t-3] + dp[2][t-3]) % MOD;
	}
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		cout << (dp[1][t]+dp[2][t]+dp[3][t]) % MOD << '\n';
	}
}
