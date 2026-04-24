#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2, MOD = 1e9+7;
vector<int> adj[MX];
int col[MX], dp[MX][4];
bool fail;
void dfs(int i, int p) {
	for(int a: adj[i]) {
		if(a == p) continue;
		dfs(a, i);
	}
	if(col[i])
		dp[i][col[i]] = 1;
	else
		dp[i][1] = dp[i][2] = dp[i][3] = 1;
	for(int a: adj[i]) {
		if(a == p) continue;
		dp[i][1] *= (dp[a][2]+dp[a][3]);
		dp[i][2] *= (dp[a][1]+dp[a][3]);
		dp[i][3] *= (dp[a][1]+dp[a][2]);
		for(int j=1; j<=3; j++)
			dp[i][j] %= MOD;
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=0; i<n-1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=0; i<k; i++) {
		int b, c;
		cin >> b >> c;
		col[b] = c;
	}
	dfs(1, 0);
	if(fail)
		return !(cout << 0);
	cout << (dp[1][1]+dp[1][2]+dp[1][3])%MOD;
}
