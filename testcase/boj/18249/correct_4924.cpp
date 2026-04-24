#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
int dp[200000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	dp[0] = dp[1] = 1;
	for(int i=2; i<=200000; i++) {
		dp[i] = (dp[i-2] + dp[i-1]) % MOD;
	}
	int t;
	cin >> t;
	while(t--) {
		int k;
		cin >> k;
		cout << dp[k] << '\n';
	}
}
