#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	vector<vector<int>> adj(n, vector<int>(n, MOD)), pre(n, vector<int>(n, MOD));
	rep(i,n) pre[i][i] = 0;
	while(k--) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		pre[u][v] = 1;
	}
	rep(t,n) {
		rep(i,n) rep(j,n) {
			adj[i][j] = min(pre[i][j], pre[i][t]+pre[t][j]);
		}
		pre = adj;
	}
	int s;
	cin >> s;
	while(s--) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		if(adj[u][v] < MOD) cout << "-1\n";
		else if(adj[v][u] < MOD) cout << "1\n";
		else cout << "0\n";
	}
}
