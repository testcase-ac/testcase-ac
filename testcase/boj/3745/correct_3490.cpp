#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
int dp[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	while(cin >> n) {
		for(int i=0; i<n; i++) {
			dp[i] = INT_MAX;
		}
		int ans = 0;
		for(int i=0; i<n; i++) {
			int t;
			cin >> t;
			int p = lower_bound(dp, dp+n, t) - dp;
			ans = max(ans, p);
			dp[p] = t;
		}
		cout << ans+1 << '\n';
	}
}
