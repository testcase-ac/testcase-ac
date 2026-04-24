#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, st, dist[101], dp[101][101][2];
int f(int l, int r, int t) {
	if(l == 1 && r == n)
		return 0;
	auto &ret = dp[l][r][t];
	if(ret != -1)
		return ret;
	ret = LLONG_MAX;
	int here = t == 0 ? l : r;
	if(l > 1)
		ret = min(ret, f(l-1,r,0)+(dist[here]-dist[l-1])*((n-r)+(l-1)));
	if(r < n)
		ret = min(ret, f(l,r+1,1)+(dist[r+1]-dist[here])*((n-r)+(l-1)));
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		cin >> n >> st;
		memset(dp, -1, sizeof dp);
		for(int i=2; i<=n; i++) {
			cin >> dist[i];
			dist[i] += dist[i-1];
		}
		cout << f(st, st, 0) << '\n';
	}
}
