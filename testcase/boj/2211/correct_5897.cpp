#include <bits/stdc++.h>
using namespace std;
const int MX = 1e3+2;
struct Path {
	int v, w;
};
struct Info {
	int u, v, w;
	bool operator<(const Info& i)const {
		return w > i.w;
	}
};
vector<Path> adj[MX];
priority_queue<Info> pq;
int dist[MX];
bool ok[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	memset(dist, 0x3f, sizeof dist);
	ok[1] = 1;
	dist[1] = 0;
	pq.push({-1,1,0});
	cout << n-1 << '\n';
	while(!pq.empty()) {
		Info t = pq.top();
		pq.pop();
		int u = t.u, v = t.v, w = t.w;
		if(w > dist[v]) continue;
		if(!ok[v]) {
			ok[v] = 1;
			cout << u << ' ' << v << '\n';
		}
		for(auto a: adj[v]) {
			if(dist[v]+a.w < dist[a.v]) {
				dist[a.v] = dist[v]+a.w;
				pq.push({v, a.v, dist[a.v]});
			}
		}
	}
}
