#include <bits/stdc++.h>
using namespace std;
const int MX = 2e5+2;
vector<int> adj[MX];
bool seen[MX];
int dfs(int i) {
	if(seen[i]) return 0;
	int sum = adj[i].size()&1;
	seen[i] = 1;
	for(int a: adj[i]) {
		sum += dfs(a);
	}
	return sum;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int ans = 0;
	for(int i=1; i<=n; i++) {
		if(!seen[i] && adj[i].size()) {
			int sum = dfs(i);
			ans += max(1, sum/2);
		}
	}
	cout << ans;
}
