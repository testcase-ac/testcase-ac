#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

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
	vector<int> dist(sz(adj), INT_MAX);
	dist[src] = 0;
	priority_queue<pair<int,int>, vector<pair<int,int>>, comp> pq;
	pq.emplace(src, 0);
	while(!pq.empty()) {
		auto v = pq.top();  // shortest path to v.first is found
		pq.pop();
		//if(dist[v.first] < v.second) continue;
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
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int N, E;
	cin >> N >> E;
	vector<vector<pair<int,int>>> adj(N);
	rep(i, E) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}
	int A, B;
	cin >> A >> B;
	A--, B--;
	vector<int> dist1 = dijkstra(adj, 0), distA = dijkstra(adj, A), distB = dijkstra(adj, B);
	bool hasans=false;
	ll ans = LLONG_MAX;
	if(distA[B] == INT_MAX) return !(cout << -1);
	if(dist1[B] != INT_MAX && distA[N-1] != INT_MAX) {
		hasans = true;
		ans = min(ans, (ll)dist1[B]+(ll)distB[A]+(ll)distA[N-1]);
	}
	if(dist1[A] != INT_MAX && distB[N-1] != INT_MAX) {
		hasans = true;
		ans = min(ans, (ll)dist1[A]+(ll)distA[B]+(ll)distB[N-1]);
	}
	if(hasans)
		cout << ans;
	else
		cout << -1;
	
}
