#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> adj[500];
int dist[500];
int path_edges[500];
bool inque[500];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a-1].push_back({b-1,c});
	}
	queue<int> que({0});
	inque[0] = true;
	memset(dist, 0x3f, sizeof dist);
	dist[0] = 0;
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		inque[u] = false;
		for(auto pr: adj[u]) {
			int v, w;
			tie(v,w) = pr;
			if(dist[u]+w<dist[v]) {
				dist[v] = dist[u]+w;
				path_edges[v] = path_edges[u]+1;
				// A strict improvement using n edges includes a negative cycle.
				if(path_edges[v] >= n) {
					cout << -1 << '\n';
					return 0;
				}
				if(!inque[v]) {
					que.push(v);
					inque[v] = true;					
				}
			}
		}
	}
	for(int i=1; i<n; i++) {
		cout << (dist[i] == 0x3f3f3f3f ? -1 : dist[i]) << '\n';
	}
}
