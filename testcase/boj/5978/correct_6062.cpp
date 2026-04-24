#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge {
	int u, i;
};
const int MX = 5e4+2;
vector<edge> adj[MX];
vector<int> ans;
bool seen[MX];
int dfs(int t, int pe) {
	if(seen[t])
		return 0;
	seen[t] = 1;
	int sz = 1;
	for(auto [u, i]: adj[t]) {
		sz += dfs(u, i);
	}
	if(sz % 2 == 0) {
		return 0;
	} else {
		if(pe == -1) {
			cout << -1;
			exit(0);
		}
		ans.push_back(pe);
		return sz;
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back({v, i});
		adj[v].push_back({u, i});
	}
	for(int i=1; i<=n; i++) {
		if(!seen[i]) {
			dfs(i, -1);
		}
	}
	cout << ans.size() << '\n';
	for(int t: ans)
		cout << t << '\n';
}
