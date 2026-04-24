#include <bits/stdc++.h>
using namespace std;
struct Edge {
	int u, w;
};
vector<Edge> adj[101];
int dp[101][101], n, m;
bool seen[101];
void dfs(int i) {
	if(seen[i])
		return;
	seen[i] = 1;
	if(adj[i].empty()) { // 기본 부품
		dp[i][i] = 1;
		return;
	}
	for(auto e: adj[i]) {
		dfs(e.u);
		for(int j=1; j<=n; j++)
			dp[i][j] += dp[e.u][j]*e.w;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	while(m--) {
		int x, y, k;
		cin >> x >> y >> k;
		adj[x].push_back({y, k});
	}
	dfs(n);
	for(int i=1; i<=n; i++) {
		if(dp[n][i])
			printf("%d %d\n", i, dp[n][i]);
	}
}
