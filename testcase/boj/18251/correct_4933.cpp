#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 18;
int arr[1<<MX];
int dp[MX][1<<MX], mn[MX][MX], cur[MX][MX], acc[MX], h_at[1<<MX];
void dfs(int i, int h, int p, int rng) {
	dp[h][p] = arr[i];
	h_at[p] = h;
	if(rng > 1) {
		dfs(i*2, h-1, p-rng/2, rng/2);
		dfs(i*2+1, h-1, p+rng/2, rng/2);
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	int hmx = 63-__builtin_clzll(n);
	dfs(1, hmx, (n+1)/2, (n+1)/2);
	for(int j=0; j<=hmx; j++) {
		for(int i=1; i<=n; i++) {
			dp[j][i] += dp[j][i-1];
		}
	}
	int ans = LLONG_MIN;
	for(int t=1; t<=n; t++) {
		acc[0] = dp[0][t];
		for(int i=0; i<=hmx; i++) {
			acc[i] = acc[i-1]+dp[i][t];
		}
		for(int i=0; i<=hmx; i++) {
			for(int j=i; j<=hmx; j++) {
				cur[i][j] = acc[j] - (i ? acc[i-1] : 0);
				if(i <= h_at[t] && h_at[t] <= j) {
					ans = max(ans, cur[i][j]-mn[i][j]);
				}
			}
		}
		for(int i=0; i<=hmx; i++) {
			for(int j=i; j<=hmx; j++) {
				mn[i][j] = min(mn[i][j], cur[i][j]);
			}
		}
	}
	cout << ans;
}
