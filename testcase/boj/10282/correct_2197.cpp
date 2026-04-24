#include <bits/stdc++.h>
using namespace std;
struct Path {
	int v, w;
	bool operator<(const Path& p)const {
		return w > p.w;
	}
};
void solve() {
	int n, d, c;
	cin >> n >> d >> c;
	vector<vector<Path>> adj(n+1);
	vector<int> dist(n+1, INT_MAX);
	while(d--) {
		int a, b, s;
		cin >> a >> b >> s;
		adj[b].push_back({a, s});
	}
	dist[c] = 0;
	priority_queue<Path> pq;
	pq.push({c, 0});
	int ans = c, cnt = 0;
	while(!pq.empty()) {
		auto pr = pq.top();
		pq.pop();
		int v = pr.v, w = pr.w;
		if(dist[v] < w) continue;
		ans = v;
		cnt++;
		for(auto a: adj[v]) {
			if(w+a.w < dist[a.v]) {
				dist[a.v] = w+a.w;
				pq.push({a.v, dist[a.v]});
			}
		}
	}
	cout << cnt << ' ' << dist[ans] << '\n';
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--)
		solve();
}
