#include <bits/stdc++.h>
using namespace std;
struct Edge {int u, c, d;};
int dp[101][10001];
vector<Edge> adj[101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, m, k;
		cin >> n >> m >> k;
		for(int i=1; i<=n; i++) {
			adj[i].clear();
		}
		while(k--) {
			int u, v, c, d;
			cin >> u >> v >> c >> d;
			adj[v].push_back({u,c,d});
		}
		memset(dp, 0x3f, sizeof dp);
		memset(dp[1], 0, sizeof dp[1]);
		for(int j=1; j<=m; j++) {
			for(int i=1; i<=n; i++) {
				dp[i][j] = dp[i][j-1];
				for(auto& e: adj[i]) {
					if(j >= e.c)
						dp[i][j] = min(dp[i][j], dp[e.u][j-e.c]+e.d);
				}
			}
		}
		if(dp[n][m] == 0x3f3f3f3f)
			cout << "Poor KCM\n";
		else
			cout << dp[n][m] << '\n';
	}
}
