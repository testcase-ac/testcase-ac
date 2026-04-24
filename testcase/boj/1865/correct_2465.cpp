#include <bits/stdc++.h>
using namespace std;
struct edge {
	int u, v, w;
};
vector<edge> arr;
int dist[600];
bool relax() {
	bool ret = 0;
	for(auto e: arr) {
		int u = e.u, v = e.v, w = e.w;
		if(dist[v] > dist[u]+w) {
			dist[v] = dist[u]+w;
			ret = 1;
		}
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int tc;
	cin >> tc;
	while(tc--) {
		arr.clear();
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0;
		int n, m, w;
		cin >> n >> m >> w;
		for(int i=0; i<m; i++) {
			int s, e, t;
			cin >> s >> e >> t;
			arr.push_back({s, e, t});
			arr.push_back({e, s, t});
		}
		for(int i=0; i<w; i++) {
			int s, e, t;
			cin >> s >> e >> t;
			arr.push_back({s, e, -t});
		}
		int t = n;
		while(t--)
			relax();
		cout << (relax() ? "YES\n" : "NO\n");
	}
}
