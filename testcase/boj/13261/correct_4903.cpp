#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 8002;
int arr[MX], acc[MX], dp[801][MX];
int f(int l, int r) {
	return (acc[r] - acc[l-1]) * (r - l + 1);
}
void solve(int i, int l, int r, int optl, int optr) {
	if(l > r)
		return;
	int m = (l+r)/2, opt = optl;
	for(int o=optl; o<=min(optr, m); o++) {
		if(dp[i-1][o-1] + f(o, m) < dp[i][m]) {
			dp[i][m] = dp[i-1][o-1] + f(o, m);
			opt = o;
		}
	}
	solve(i, l, m-1, optl, opt);
	solve(i, m+1, r, opt, optr);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		acc[i] = acc[i-1] + arr[i];
	}
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = 0;
	m = min(m, n);
	for(int i=1; i<=m; i++) {
		solve(i, i, n, i, n);
	}
	cout << dp[m][n];
}
