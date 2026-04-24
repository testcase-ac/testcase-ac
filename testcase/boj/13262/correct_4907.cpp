#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[5001][5001], ored[5001][5001], arr[5001];
void f(int i, int l, int r, int optl, int optr) {
	if(l > r) return;
	int m = (l+r)/2;
	int opt = optl;
	for(int j=optl; j<=min(m, optr); j++) {
		int v = dp[i-1][j-1]+ored[j][m];
		if(v > dp[i][m]) {
			dp[i][m] = v;
			opt = j;
		}
	}
	f(i, l, m-1, optl, opt);
	f(i, m+1, r, opt, optr);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		int val = arr[i];
		for(int j=i; j>=1; j--) {
			val = val | arr[j];
			ored[j][i] = val;
		}
	}
	for(int i=1; i<=k; i++) {
		f(i, i, n-k+i, i, n-k+i);
	}
	cout << dp[k][n];
}
