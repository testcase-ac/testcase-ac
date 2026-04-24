#include <bits/stdc++.h>
using namespace std;
const int MX = 5e6+2;
int dp[MX], lst[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t, a, b;
	cin >> t >> a >> b;
	dp[0] = 1;
	int cl = 0;
	for(int i=1; i<=t; i++) {
		if(i-a >= 0)
			dp[i] = dp[i-a];
		if(i-b >= 0)
			dp[i] |= dp[i-b];
		if(dp[i])
			cl = i;
		lst[i] = cl;
	}
	int ans = lst[t];;
	for(int i=t; i; i--) {
		if(dp[i]) {
			int p = i/2;
			ans = max(ans, p+lst[t-p]);
		}
	}
	cout << ans;
}
