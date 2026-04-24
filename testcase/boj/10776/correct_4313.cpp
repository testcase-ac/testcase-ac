#include <bits/stdc++.h>
using namespace std;
#define int long long
int dist[201][2002];
struct info {
	int a, b, w;
	bool operator<(const info& d) const {
		return w > d.w;
	}
};
struct edge {
	int u, t, h;
};
vector<edge> adj[2002];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int k, n, m, A, B;
	cin >> k >> n >> m;
	priority_queue<info> pq;
	for(int i=0; i<m; i++) {
		int a, b, t, h;
		cin >> a >> b >> t >> h;
		adj[a].push_back({b, t, h});
		adj[b].push_back({a, t, h});
	}
	memset(dist, 0x3f, sizeof dist);
	cin >> A >> B;
	dist[0][A] = 0;
	pq.push({0, A, 0});
	int mn = LLONG_MAX;
	while(pq.size()) {
		auto [a, b, w] = pq.top();
		pq.pop();
		if(b == B)
			mn = min(mn, w);
		if(dist[a][b] < w)
			continue;
		for(auto [nb, t, h]: adj[b]) {
			int na = a + h;
			if(na >= k) continue;
			if(dist[na][nb] > w + t) {
				dist[na][nb] = w+t;
				pq.push({na, nb, dist[na][nb]});
			}
		}
	}
	cout << (mn == LLONG_MAX ? -1ll : mn);
}
