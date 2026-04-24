#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
vector<int> adj[MX];
int mn[MX];
int dfs(int i, int p, int h) {
	int ret = 0;
	for(int a: adj[i]) {
		if(a == p) continue;
		ret += dfs(a, i, h+1);
		mn[i] = min(mn[i], mn[a]+1);
	}
	if(!ret)
		mn[i] = 0;
	if(mn[i] <= h)
		return 1;
	else
		return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=0; i<n-1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	memset(mn, 0x3f, sizeof mn);
	cout << dfs(k, 0, 0);
}
