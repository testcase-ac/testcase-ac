#include <bits/stdc++.h>
using namespace std;
#define int long long
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

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a-1].push_back(b-1);
		adj[b-1].push_back(a-1);
	}
	LCA lca(0, adj);
	int q, t, ans = 0;
	cin >> q >> t;
	t--;
	q--;
	while(q--) {
		int nxt;
		cin >> nxt;
		nxt--;
		int p = lca.query(t, nxt);
		ans += lca.depth[t] + lca.depth[nxt] - 2*lca.depth[p];
		//printf("q %d, %d, ans = %d\n", t, nxt, ans);
		t = nxt;
	}
	cout << ans;
}
