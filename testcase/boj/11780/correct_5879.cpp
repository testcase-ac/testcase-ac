#include <bits/stdc++.h>
using namespace std;
int arr[101][101];
struct Path {
	int u, w;
	bool operator<(const Path& p) const {
		return w > p.w;
	}
};
int prv[101], n, INF = 0x3f3f3f3f;
vector<int> dists[101];
vector<int> ans[101][101];
void f(int s) {
	vector<int>& dist = dists[s];
	dist.resize(n+1, INF);
	memset(prv, -1, sizeof prv);
	dist[s] = 0;
	priority_queue<Path> pq;
	pq.push({s,0});
	while(!pq.empty()) {
		auto p = pq.top();
		pq.pop();
		int u = p.u, w = p.w;
		if(dist[u] < w) continue;
		for(int i=1; i<=n; i++) {
			if(w+arr[u][i] < dist[i]) {
				dist[i] = w+arr[u][i];
				prv[i] = u;
				pq.push({i, dist[i]});
			}
		}
	}
	for(int i=1; i<=n; i++) {
		vector<int>& path = ans[s][i];
		if(i == s || dist[i] == INF) {
			continue;
		}
		int t = i;
		while(t != -1) {
			path.push_back(t);
			t = prv[t];
		}
		reverse(path.begin(), path.end());
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int m;
	cin >> n >> m;
	memset(arr, 0x3f, sizeof arr);
	for(int i=1; i<=n; i++) {
		arr[i][i] = 0;
	}
	for(int i=0; i<m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		arr[a][b] = min(arr[a][b], c);
	}
	for(int i=1; i<=n; i++) {
		f(i);
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cout << (dists[i][j] == INF || i == j ? 0 : dists[i][j]) << ' ';
		}
		cout << '\n';
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cout << ans[i][j].size() << ' ';
			for(int k: ans[i][j])
				cout << k << ' ';
			cout << '\n';
		}
	}
}
