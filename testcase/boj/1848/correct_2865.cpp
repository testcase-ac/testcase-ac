#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge {
	int u, w;
	bool operator< (const edge& e) const {
		return w > e.w;
	}
};
const int MX = 5001;
vector<edge> adj[MX];
int in[MX], dist[MX], ans = INT_MAX, n, m;
void f(int b, int is) {
	priority_queue<edge> pq;
	memset(dist, 0x3f, sizeof dist);
	auto st = [&](int t){return !!(t & (1 << b)) == is && in[t];};
	for(int i=2; i<=n; i++) {
		if(st(i)) {
			dist[i] = in[i];
			pq.push({i, in[i]});
		}
	}
	while(pq.size()) {
		auto [u, w] = pq.top();
		pq.pop();
		if(w > dist[u]) continue;
		for(auto [eu, ew]: adj[u]) {
			if(st(u) && eu == 1) continue;
			if(dist[eu] > w + ew) {
				dist[eu] = w + ew;
				pq.push({eu, dist[eu]});
			}
		}
	}
	ans = min(ans, dist[1]);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	vector<pair<int, int>> sts;
	for(int i=0; i<m; i++) {
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		if(u == 1) {
			in[v] = a;
		} else if(v == 1) {
			in[u] = b;
		}
		adj[u].push_back({v, a});
		adj[v].push_back({u, b});
	}
	for(int b=0; b<=12; b++) {
		f(b, 0);
		f(b, 1);
	}
	cout << ans;
}
