#include <bits/stdc++.h>
using namespace std;

int dp[10001][10001], ans[10000], n, k, l;
inline bool ok(int u, int w) {
	// 2u/w >= k/l -> ul>=kw
	return 2*u*l >= k*w;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> k >> l;
	string s;
	cin >> s;
	for(int d=2; d<=n; d++) {
		for(int i=0; i<=n-d; i++) {
			int j = i+d;
			if(s[i] == s[j-1])
				dp[i][j] = dp[i+1][j-1]+1;
		}
	}
	ans[0] = 1e9;
	for(int i=1; i<n; i++) {
		if(ok(dp[0][i+1],i+1))
			ans[i] = 1;
		else {
			ans[i] = 1e9;
			for(int j=0; j<i; j++) {
				if(ok(dp[j+1][i+1], i-j))
					ans[i] = min(ans[i], ans[j]+1);
			}
		}
	}
	cout << (ans[n-1] == 1e9 ? 0 : ans[n-1]);
}
