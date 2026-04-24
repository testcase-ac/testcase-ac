#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge{int u, v, w, i;};
const int MX = 2e5+2, MXLG = 19;
int par[MX], spw[MXLG][MX], spw2[MXLG][MX], spp[MXLG][MX], height[MX];
vector<pair<int, int>> adj[MX];
vector<edge> edges;
bool used[MX];
int f(int i){return i==par[i]?i:par[i]=f(par[i]);}
void dfs(int i, int p, int h) {
	height[i] = h;
	for(auto [v, w]: adj[i]) {
		if(v == p) continue;
		spw[0][v] = w;
		spw2[0][v] = -1;
		spp[0][v] = i;
		dfs(v, i, h+1);
	}
}
void mx2(vector<int> v, int& m1, int& m2) {
	assert(v.size() >= 2);
	sort(v.begin(), v.end(), greater<int>());
	unique(v.begin(), v.end());
	m1 = v[0];
	m2 = v[1];
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edges.push_back({u, v, w, i});
	}
	for(int i=1; i<=n; i++)
		par[i] = i;
	sort(edges.begin(), edges.end(), [](edge a, edge b){return a.w < b.w;});
	int curw = 0;
	for(int i=0; i<m; i++) {
		auto e = edges[i];
		int u = f(e.u), v = f(e.v);
		if(u == v) continue;
		par[u] = v;
		curw += e.w;
		used[e.i] = 1;
		adj[e.u].push_back({e.v, e.w});
		adj[e.v].push_back({e.u, e.w});
	}
	sort(edges.begin(), edges.end(), [](edge a, edge b){return a.i < b.i;});
	spw[0][1] = spw2[0][1] = -1;
	spp[0][1] = 1;
	dfs(1, 0, 0);
	for(int i=1; i<MXLG; i++) {
		for(int j=1; j<=n; j++) {
			spp[i][j] = spp[i-1][spp[i-1][j]];
			mx2({spw[i-1][j], spw2[i-1][j], spw[i-1][spp[i-1][j]], spw2[i-1][spp[i-1][j]]}, spw[i][j], spw2[i][j]);
		}
	}
	for(int t=0; t<m; t++) {
		if(used[t]) {
			cout << curw << '\n';
			continue;
		}
		edge e = edges[t];
		int u = e.u, v = e.v, w = e.w, m1 = -1, m2 = -2;
		if(height[u] < height[v])
			swap(u, v);
		int diff = height[u] - height[v];
		for(int i=0; i<MXLG; i++) {
			if(diff&(1<<i)) {
				mx2({m1, m2, spw[i][u], spw2[i][u]}, m1, m2);
				u = spp[i][u];
			}
		}
		for(int i=MXLG-1; i>=0; i--) {
			if(spp[i][u] != spp[i][v]) {
				mx2({m1, m2, spw[i][v], spw2[i][v], spw[i][u], spw2[i][u]}, m1, m2);
				u = spp[i][u];
				v = spp[i][v];
			}
		}
		if(u != v) {
			mx2({m1, m2, spw[0][u], spw[0][v]}, m1, m2);
		}
		//printf("for edge of u, v, w=%lld, %lld, %lld, m1=%lld, m2=%lld\n", e.u, e.v, w, m1, m2);
		cout << curw + (w - m1) << '\n';
	}
}
