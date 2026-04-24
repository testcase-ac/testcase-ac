#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
vector<vector<int>> adj;
vector<int> num, low, stk, scc, indeg;
int nxt, nxtscc;
void dfs(int i) {
	num[i] = low[i] = nxt++;
	stk.push_back(i);
	for(int a: adj[i]) {
		if(!num[a])
			dfs(a);
		if(!scc[a])
			low[i] = min(low[i], low[a]);
		else
			indeg[scc[a]]++;
	}
	if(num[i] == low[i]) {
		int s = nxtscc++;
		while(1) {
			int t = stk.back();
			stk.pop_back();
			scc[t] = s;
			if(t == i) break;
		}
	}
}
int solve() {
	int n, m;
	cin >> n >> m;
	adj = vector<vector<int>>(n+1);
	num = low = scc = indeg = vector<int>(n+1);
	nxt = nxtscc = 1;
	while(m--) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
	}
	for(int i=1; i<=n; i++) {
		if(!num[i])
			dfs(i);
	}
	int ans = 0;
	for(int i=1; i<nxtscc; i++) {
		if(!indeg[i])
			ans++;
	}
	return ans;
}
int main() {
	int T;
	cin >> T;
	while(T--)
		cout << solve() << '\n';
}
