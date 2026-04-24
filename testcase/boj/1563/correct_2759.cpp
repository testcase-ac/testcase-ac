#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000
int dp[1000][2][4]; // days/late cnt/last one?(O/L/A1/A2)
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	dp[0][0][0] = 1;
	dp[0][1][1] = 1;
	dp[0][0][2] = 1;
	int n;
	cin >> n;
	for(int i=1; i<n; i++) {
		dp[i][0][0] = (dp[i-1][0][0] + dp[i-1][0][2] + dp[i-1][0][3]) % MOD;
		dp[i][0][2] = dp[i-1][0][0];
		dp[i][0][3] = dp[i-1][0][2];
		dp[i][1][0] = accumulate(dp[i-1][1], dp[i-1][1]+4, 0) % MOD;
		dp[i][1][1] = accumulate(dp[i-1][0], dp[i-1][0]+4, 0) % MOD;
		dp[i][1][2] = (dp[i-1][1][0] + dp[i-1][1][1]) % MOD;
		dp[i][1][3] = dp[i-1][1][2];
	}
	int ans = 0;
	for(int i=0; i<2; i++) {
		for(int j=0; j<4; j++) {
			ans += dp[n-1][i][j];
		}
	}
	cout << (ans % MOD);
}
