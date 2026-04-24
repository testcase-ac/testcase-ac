#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> adj[500];
int dist[500];
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
	int cnt = 0;
	queue<int> que({0});
	inque[0] = true;
	memset(dist, 0x3f, sizeof dist);
	dist[0] = 0;
	const int lim = (n*n < 1000 ? n*n : n*n/2);
	while(!que.empty() && cnt < lim) {
		int u = que.front();
		que.pop();
		inque[u] = false;
		for(auto pr: adj[u]) {
			int v, w;
			tie(v,w) = pr;
			if(dist[u]+w<dist[v]) {
				dist[v] = dist[u]+w;
				if(!inque[v]) {
					que.push(v);
					inque[v] = true;					
				}
			}
		}
		cnt++;
	}
	if(cnt == lim)
		return !(cout << -1);
	for(int i=1; i<n; i++) {
		cout << (dist[i] == 0x3f3f3f3f ? -1 : dist[i]) << '\n';
	}
}
