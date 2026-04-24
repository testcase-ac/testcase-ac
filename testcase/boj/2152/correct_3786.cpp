#include <bits/stdc++.h>
using namespace std;
const int MX = 1e4+1;
vector<int> adj[MX], stk;
int sccw[MX], low[MX], num[MX], instk[MX], nxt = 1, goal;
void dfs(int i) {
	if(num[i]) return;
	instk[i] = 1;
	stk.push_back(i);
	num[i] = low[i] = nxt++;
	for(int a: adj[i]) {
		dfs(a);
		if(instk[a])
			low[i] = min(low[i], low[a]);
	}
	if(num[i] == low[i]) {
		int mx = 0, w = 0, reached = 0;
		while(1) {
			int t = stk.back();
			stk.pop_back();
			instk[t] = 0;
			if(t == goal)
				reached = 1;
			for(int a: adj[t]) {
				mx = max(mx, sccw[low[a]]);
			}
			w++;
			if(t == i)
				break;
		}
		if(mx)
			sccw[low[i]] = w+mx;
		else if(reached)
			sccw[low[i]] = w;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	goal = t;
	for(int i=0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
	dfs(s);
	cout << sccw[1];
}
