#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int dist[251][251];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	memset(dist, 0x3f, sizeof dist);
	for(int i=0; i<n; i++) {
		dist[i][i] = 0;
	}
	while(m--) {
		int u, v, b;
		cin >> u >> v >> b;
		u--, v--;
		dist[u][v] = 0;
		dist[v][u] = !b;
	}
	for(int k=0; k<n; k++) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
			}
		}
	}
	int q;
	cin >> q;
	while(q--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		cout << dist[a][b] << '\n';
	}
}
