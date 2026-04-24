#include <bits/stdc++.h>
using namespace std;
struct Edge {
	int t, v;
};
const int MX = 1e5+1;
vector<Edge> adj[MX];
int color[MX], n, m;
bool dfs(int i, int t) {
	for(auto e: adj[i]) {
		if(e.t <= t) {
			if(color[e.v] == -1) {
				color[e.v] = !color[i];
				if(!dfs(e.v, t))
					return 0;
			} else if(color[e.v] == color[i])
				return 0;
		}
	}
	return 1;
}
bool check(int t) {
	memset(color, -1, sizeof color);
	for(int i=1; i<=n; i++) {
		if(color[i] == -1) {
			color[i] = 0;
			if(!dfs(i, t))
				return 0;
		}
	}
	return 1;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=1; i<=m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back({i, b});
		adj[b].push_back({i, a});
	}
	int l = 1, r = m;
	while(l < r) {
		int t = (l+r+1)/2;
		if(check(t))
			l = t;
		else
			r = t-1;
	}
	cout << l+1;
}
