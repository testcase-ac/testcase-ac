#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+3;
// Heavy-light decomposition implementation adapted for this solution.
// Reference: https://cp-algorithms.com/graph/hld.html
struct Edge{int u, w, i;};
vector<Edge> adj[MX];
int n, par[MX], dep[MX], heavy[MX], head[MX], pos[MX], segt[MX*2], e2v[MX], cpos;
void upd(int i, int v) {
	i += n;
	segt[i] = v;
	while(i /= 2)
		segt[i] = max(segt[i*2], segt[i*2+1]);
}
int qry(int l, int r) { // [l, r)
	int res = 0;
	l += n, r += n;
	while(l < r) {
		if(l&1) res = max(res, segt[l++]);
		if(r&1) res = max(res, segt[--r]);
		l /= 2, r /= 2;
	}
	return res;
}
int dfs(int i) {
	int sz = 1, mx = 0;
	for(auto a: adj[i]) {
		if(a.u == par[i]) continue;
		par[a.u] = i;
		dep[a.u] = dep[i]+1;
		int t = dfs(a.u);
		sz += t;
		if(t > mx) {
			mx = t;
			heavy[i] = a.u;
		}
	}
	return sz;
}
void build(int i, int h) {
	head[i] = h, pos[i] = cpos;
	cpos++;
	if(heavy[i])
		build(heavy[i], h);
	for(auto a: adj[i]) {
		if(a.u == par[i]) continue;
		if(a.u != heavy[i])
			build(a.u, a.u);
		e2v[a.i] = a.u;
		upd(pos[a.u], a.w);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=1; i<=n-1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v,w,i});
		adj[v].push_back({u,w,i});
	}
	dfs(1);
	build(1, 1);
	int m;
	cin >> m;
	while(m--) {
		int t, a, b;
		cin >> t >> a >> b;
		if(t == 1)
			upd(pos[e2v[a]], b);
		else {
			int r = 0;
			while(head[a] != head[b]) {
				if(dep[head[a]] < dep[head[b]])
					swap(a,b);
				r = max(r, qry(pos[head[a]],pos[a]+1));
				a = par[head[a]];
			}
			if(pos[a] > pos[b]) swap(a, b);
			r = max(r, qry(pos[a]+1, pos[b]+1));
			cout << r << '\n';
		}
	}
}
