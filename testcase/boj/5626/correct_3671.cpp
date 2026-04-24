#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e4, MOD = 1e9+7;
int dp[2][MX+1][2], arr[MX+1];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	dp[0][0][0] = 1;
	for(int i=1; i<=n; i++) {
		int c = i&1, p = c^1;
		memset(dp[c], 0, sizeof(dp[c]));
		for(int j=0; j<=MX; j++) {
			if(arr[i] != -1 && arr[i] != j) {
				continue;
			}
			dp[c][j][0] = dp[p][j+1][0] + dp[p][j][0]+(j ? dp[p][j-1][1] : 0);
			dp[c][j][1] = dp[p][j+1][0] + dp[p][j][0]+(j ? dp[p][j-1][1] : 0);
			dp[c][j][0] %= MOD;
			dp[c][j][1] %= MOD;
		}
	}
	int res = 1, mult = 2, p = MOD-2;
	while(p) {
		if(p&1) res = (res*mult)%MOD;
		mult = (mult*mult)%MOD;
		p /= 2;
	}
	cout << ((dp[n&1][0][0] + dp[n&1][0][1])*res) % MOD;
}
