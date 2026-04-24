#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int dp[n];
	memset(dp, 0x3f, sizeof dp);
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		*lower_bound(dp, dp+n, t) = t;
	}
	cout << lower_bound(dp, dp+n, 0x3f3f3f3f) - dp;
}
