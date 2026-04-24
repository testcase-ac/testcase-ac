#include <bits/stdc++.h>
using namespace std;
struct LCA {
	int n, lg;
	vector<vector<int>> dp;
	vector<int> depth;
	LCA(int root, vector<vector<int>>& adj) {
		n = adj.size();
		lg = 32 - __builtin_clz(n);
		dp.resize(lg, vector<int>(n));
		depth.resize(n);
		dfs(root, root, 0, adj);
		for(int i=1; i<lg; i++) {
			for(int j=0; j<n; j++) {
				dp[i][j] = dp[i-1][dp[i-1][j]];
			}
		}
	}
	void dfs(int i, int p, int d, vector<vector<int>>& adj) {
		depth[i] = d;
		dp[0][i] = p;
		for(int a: adj[i]) {
			if(a == p) continue;
			dfs(a, i, d+1, adj);
		}
	}
	int query(int a, int b) {
		if(depth[a] > depth[b])
			swap(a, b);
		int d = depth[b] - depth[a];
		for(int i=0; i<lg; i++) {
			if(d&(1<<i))
				b = dp[i][b];
		}
		if(a == b)
			return a;
		for(int i=lg-1; i>=0; i--) {
			if(dp[i][a] != dp[i][b]) {
				a = dp[i][a];
				b = dp[i][b];
			}
		}
		a = dp[0][a];
		b = dp[0][b];
		assert(a == b);
		return a;
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	LCA lca(0, adj);
	int q;
	cin >> q;
	while(q--) {
		int r, u, v;
		cin >> r >> u >> v;
		r--, u--, v--;
		vector<int> a = {lca.query(r, u), lca.query(r, v), lca.query(u, v)};
		cout << *max_element(a.begin(), a.end(), [&](int x, int y){return lca.depth[x] < lca.depth[y];}) + 1 << '\n';
	}
}
