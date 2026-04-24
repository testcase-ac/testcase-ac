#include <bits/stdc++.h>
using namespace std;
const int MX = 5e3+1, MOD = 1e9+7;
int dp[MX][MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	dp[0][0] = 1;
	for(int i=1; i<MX; i++) {
		for(int j=0; j<=i; j++) {
			int& r = dp[i][j];
			if(j)
				r += dp[i-1][j-1];
			if(j != i)
				r += dp[i-1][j+1];
			r %= MOD;
		}
	}
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		cout << dp[n][0] << '\n';
	}
}
