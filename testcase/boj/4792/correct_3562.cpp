#include <bits/stdc++.h>
using namespace std;
int getcc(vector<vector<int>>& adj) {
	vector<bool> seen(adj.size());
	int num = 0;
	function<void(int)> dfs = [&](int i) {
		if(seen[i]) return;
		seen[i] = 1;
		for(int a: adj[i]) {
			dfs(a);
		}
	};
	for(int i=1; i<adj.size(); i++) {
		if(!seen[i]) {
			dfs(i);
			num++;
		}
	}
	return num;
}
bool solve(){
	int n, m, k, bcnt = 0;
	cin >> n >> m >> k;
	if(!n) exit(0);
	vector<vector<int>> adjb(n+1), adjr(n+1);
	for(int i=0; i<m; i++) {
		char c;
		int u, v;
		cin >> c >> u >> v;
		if(c == 'B') {
			bcnt++;
			adjb[u].push_back(v);
			adjb[v].push_back(u);
		} else {
			adjr[u].push_back(v);
			adjr[v].push_back(u);
		}
	}
	int x = getcc(adjb);
	int y = getcc(adjr);
	int ub = n-x, lb = y-1;
	return lb <= k && k <= ub;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1)
		cout << solve() << '\n';
}
