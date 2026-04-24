#include <bits/stdc++.h>
using namespace std;
const int MX = 100000;
vector<int> adj[MX];
int num[MX], low[MX], parent[MX], ind = 1;
bool isarti[MX]; // for articulation point
vector<pair<int, int>> ans; // for articulation bridge
int dfs(int u, bool isroot) {
	num[u] = low[u] = ind++;
	int childcnt = 0;
	for(int a: adj[u]) {
		if(a == parent[u]) continue;
		if(num[a]) {
			low[u] = min(low[u], num[a]);
		} else {
			childcnt++;
			parent[a] = u;
			low[u] = min(low[u], dfs(a, false));
			// for articulation point:
			if(low[a] >= num[u])
				isarti[u] = true;
			// for articulation bridge:
			if(low[a] > num[u])
				ans.emplace_back(min(a,u), max(a,u));
		}
	}
	if(isroot) isarti[u] = (childcnt>=2); // for articulation point
	return low[u];
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int v, e;
	cin >> v >> e;
	while(e--) {
		int a, b;
		cin >> a >> b;
		adj[a-1].push_back(b-1);
		adj[b-1].push_back(a-1);
	}
	for(int i=0; i<v; i++) {
		if(!num[i]) {
			dfs(i, true);
		}
	}
	vector<int> ansv;
	for(int i=0; i<v; i++) {
		if(isarti[i])
			ansv.push_back(i+1);
	}
	cout << ansv.size() << '\n';
	for(int a: ansv) cout << a << ' ';
}
