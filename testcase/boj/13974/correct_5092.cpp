#include <bits/stdc++.h>
using namespace std;
int dp[5000][5000], cut[5000][5000], a[5000], acc[5000];
int solve() {
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> a[i];
		acc[i] = (i ? acc[i-1] : 0) + a[i];
	}
	for(int i=0; i<n; i++) {
		dp[i][i] = 0;
		if(i != n-1) {
			dp[i][i+1] = a[i]+a[i+1];
			cut[i][i+1] = i;
		}
		cut[i][i] = i;
	}
	for(int l=2; l<n; l++) {
		for(int i=0; i+l<n; i++) {
			int j = i+l;
			dp[i][j] = INT_MAX;
			for(int k=max(i, cut[i][j-1]); k<=min(j-1, cut[i+1][j]); k++) {
				if(dp[i][j] > dp[i][k]+dp[k+1][j]) {
					dp[i][j] = dp[i][k]+dp[k+1][j];
					cut[i][j] = k;
				}
			}
			dp[i][j] += acc[j]-(i ? acc[i-1] : 0);
		}
	}
	return dp[0][n-1];
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		cout << solve() << '\n';
	}
}
