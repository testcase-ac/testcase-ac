#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

struct comp {
	bool operator()(const pair<int,int> a, const pair<int,int> b) const {
		return a.second > b.second;
	}
};

vector<int> dijkstra(vector<vector<pair<int,int>>> &adj, int src) {  // pair in adj: (node index, distance)
	vector<int> dist(sz(adj), MOD);
	dist[src] = 0;
	priority_queue<pair<int,int>, vector<pair<int,int>>, comp> pq;
	pq.emplace(src, 0);
	while(!pq.empty()) {
		auto v = pq.top();  // shortest path to v.first is found
		pq.pop();
		if(dist[v.first] < v.second) continue;
		for(auto pr: adj[v.first]) {
			if(v.second + pr.second < dist[pr.first]) {
				dist[pr.first] = v.second + pr.second;
				pq.emplace(pr.first, dist[pr.first]);
			}
		}
	}
	return dist;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m, x;
	cin >> n >> m >> x; x--;
	vector<vector<pair<int,int>>> adj(n), adjrev(n);
	rep(i, m) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		adj[u].emplace_back(v, w);
		adjrev[v].emplace_back(u, w);
	}
	vector<int> dist, distrev;
	dist = dijkstra(adj, x);
	distrev = dijkstra(adjrev, x);
	int ans = 0;
	rep(i, n) {
		dist[i] += distrev[i];
		ans = max(ans, dist[i]);
	}
	cout << ans;
}
