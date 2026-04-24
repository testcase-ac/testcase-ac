#include <bits/stdc++.h>
using namespace std;
#define int long long
struct LCA {
    int n, lg;
    vector<vector<int>> dp;
    vector<vector<int>> bms;
    vector<int> depth;
    LCA(int root, vector<vector<int>>& adj, vector<int>& val) {
        n = adj.size();
        lg = 32 - __builtin_clz(n);
        dp.resize(lg, vector<int>(n));
        bms.resize(lg, vector<int>(n));
        depth.resize(n);
        dfs(root, root, 0, adj, val); // p=root for dp table
        for(int i=1; i<lg; i++) {
            for(int j=0; j<n; j++) {
                dp[i][j] = dp[i-1][dp[i-1][j]];
                bms[i][j] = bms[i-1][j] | bms[i-1][dp[i-1][j]];
            }
        }
    }
    void dfs(int i, int p, int d, vector<vector<int>>& adj, vector<int>& val) {
        depth[i] = d;
        dp[0][i] = p;
        bms[0][i] = 1<<val[i];
        for(int a: adj[i]) {
            if(a == p) continue;
            dfs(a, i, d+1, adj, val);
        }
    }
    pair<int, int> query(int a, int b) {
        if(depth[a] > depth[b])
            swap(a, b);
        int d = depth[b] - depth[a];
        int val = 0;
        for(int i=0; i<lg; i++) {
            if(d&(1<<i)) {
                val |= bms[i][b];
                b = dp[i][b];
            }
        }
        if(a == b)
            return {a, val};
        for(int i=lg-1; i>=0; i--) {
            if(dp[i][a] != dp[i][b]) {
            	val |= bms[i][a];
            	val |= bms[i][b];
                a = dp[i][a];
                b = dp[i][b];
            }
        }
        val |= bms[0][a];
        val |= bms[0][b];
        a = dp[0][a];
        b = dp[0][b];
        assert(a == b);
        return {a, val};
    }
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> val(n+1);
	int allbms = 0;
	for(int i=1; i<=n; i++) {
		cin >> val[i];
		allbms |= 1<<val[i];
	}
	vector<vector<int>> adj(n+1);
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	LCA lca(1, adj, val);
	int m, last_a = -1;
	cin >> m;
	for(int i=0; i<m; i++) {
		int a, v;
		cin >> a >> v;
		if(!i) {
			if((1<<v) & allbms)
				cout << "PLAY\n";
			else
				cout << "CRY\n";
		} else {
			auto [l, bms] = lca.query(last_a, a);
			//printf("last_a = %d, a = %d, l = %d, bms = %d\n", last_a, a, l, bms);
			bms |= 1<<val[l];
			if((1<<v) & bms) {
				cout << "PLAY\n";
			} else {
				cout << "CRY\n";
			}
		}
		last_a = a;
	}
}
