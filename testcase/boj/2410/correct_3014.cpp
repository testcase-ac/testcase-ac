#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000000, MX = 1000007;
int dp[20][MX];
// dp[i][n] = sum(dp[i-1][n-k*(1<<i)] for all k s.t. n-k*(1<<i) >= 0)
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	int highest = 31 - __builtin_clz(n);
	for(int i=0; i<=n; i++)
		dp[0][i] = 1;
	for(int i=1; i<=highest; i++) {
		for(int j=0; j<(1<<i); j++)
			dp[i][j] = dp[i-1][j];
		for(int j=1<<i; j<=n; j++) {
			dp[i][j] = (dp[i][j-(1<<i)] + dp[i-1][j]) % MOD;
		}
	}
	cout << dp[highest][n];
}
