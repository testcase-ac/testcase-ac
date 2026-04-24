#include <bits/stdc++.h>
using namespace std;
#define MX 1000
int parent[MX], dist[MX];
struct Path {
	int v, w;
	bool operator< (const Path &i) const {return w > i.w;}
};
vector<Path> adj[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++)
		dist[i] = 1e9+7;
	while(m--) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u-1].push_back({v-1,w});
	}
	int start, end;
	cin >> start >> end;
	start--, end--;
	memset(parent, -1, sizeof parent);
	priority_queue<Path> pq;
	pq.push({start, 0});
	dist[start] = 0;
	while(!pq.empty()) {
		auto p = pq.top();
		pq.pop();
		if(p.v == end) break;
		for(auto a: adj[p.v]) {
			if(p.w + a.w < dist[a.v]) {
				dist[a.v] = p.w + a.w;
				pq.push({a.v, dist[a.v]});
				parent[a.v] = p.v;
			}
		}
	}
	vector<int> ans = {end};
	int now = end;
	while(parent[now] != -1) {
		ans.push_back(parent[now]);
		now = parent[now];
	}
	reverse(ans.begin(), ans.end());
	cout << dist[end] << '\n' << (int)ans.size() << '\n';
	for(int a: ans) cout << a+1 << ' ';
}
