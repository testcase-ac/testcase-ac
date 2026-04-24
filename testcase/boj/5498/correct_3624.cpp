#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e4+2;
int t[MX], tac[MX], f[MX], fac[MX], s, dp[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n >> s;
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	for(int i=1; i<=n; i++) {
		cin >> t[i] >> f[i];
		tac[i] = tac[i-1] + t[i];
		fac[i] = fac[i-1] + f[i];
	}
	for(int i=1; i<=n; i++) {
		for(int j=0; j<i; j++) {
			dp[i] = min(dp[i], dp[j] + (fac[n] - fac[j]) * (s + tac[i] - tac[j]));
		}
	}
	cout << dp[n];
}
