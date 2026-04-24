#include <bits/stdc++.h>
using namespace std;
const int MXN = 1e5+2, MXK = 1e3+2;
int tubes[MXK][MXK], dist[MXN], n, k, m;
bool tseen[MXK], nseen[MXN];
vector<int> adjt[MXN];
queue<int> que;
void relax(int i) {
	for(int t: adjt[i]) {
		if(tseen[t]) continue;
		tseen[t] = 1;
		for(int j=0; j<k; j++) {
			int u = tubes[t][j];
			if(!nseen[u]) {
				que.push(u);
				dist[u] = dist[i]+1;
				nseen[u] = 1;
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> k >> m;
	memset(dist, -1, sizeof dist);
	for(int i=0; i<m; i++) {
		for(int j=0; j<k; j++) {
			cin >> tubes[i][j];
			adjt[tubes[i][j]].push_back(i);
		}
	}
	dist[1] = 1;
	nseen[1] = 1;
	relax(1);
	while(!que.empty()) {
		int q = que.front();
		que.pop();
		relax(q);
	}
	cout << dist[n];
}
