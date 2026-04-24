#include <bits/stdc++.h>
using namespace std;

long long dp[65][10], ans[65];

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0; i<10; i++) {
		dp[1][i] = 1;
	}
	for(int i=2; i<=64; i++) {
		dp[i][0] = dp[i-1][0];
		for(int j=1; j<=9; j++) {
			dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}
	for(int i=1; i<=64; i++) {
		ans[i] = accumulate(dp[i], dp[i]+10, 0LL);
	}
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		cout << ans[n] << '\n';
	}
}
