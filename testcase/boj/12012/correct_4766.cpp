#include <bits/stdc++.h>
using namespace std;
const int MX = 2e5+2;
vector<int> adj[MX];
int par[MX];
int f(int i){return i == par[i] ? i : par[i] = f(par[i]);}
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
	vector<int> a(n), ans;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	reverse(a.begin(), a.end());
	int stcnt = 0;
	for(int t: a) {
		par[t] = t;
		stcnt++;
		for(int p: adj[t]) {
			if(par[p] && f(t) != f(p)) {
				stcnt--;
				par[f(t)] = f(p);
			}
		}
		ans.push_back(stcnt == 1);
	}
	reverse(ans.begin(), ans.end());
	for(int t: ans)
		cout << (t ? "YES\n" : "NO\n");
}
