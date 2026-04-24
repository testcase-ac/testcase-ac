#include <bits/stdc++.h>
using namespace std;
//https://www.acmicpc.net/source/10065112
const int MX = 4003;
vector<pair<int, int>> adj[MX];
int foxd[MX], wolfd[2][MX];
struct Path {
	int u, d, sp;
	bool operator< (const Path &p) const {
		return d > p.d;
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) foxd[i] = wolfd[0][i] = wolfd[1][i] = 2e9;
	while(m--) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v,2*w});  // first=node, second=scaled distance
		adj[v].push_back({u,2*w});
	}
	priority_queue<Path> pq;
	pq.push({1,0,0});
	while(!pq.empty()) {
		Path p = pq.top();
		pq.pop();
		int u = p.u, d = p.d;
		if(d > foxd[u]) continue;
		for(auto pr: adj[u]) {
			if(d + pr.second < foxd[pr.first]) {
				foxd[pr.first] = d + pr.second;
				pq.push({pr.first, d+pr.second, 0});
			}
		}
	}

	pq.push({1,0,0});
	while(!pq.empty()) {
		Path p = pq.top();
		pq.pop();
		int u = p.u, d = p.d, sp = !p.sp;
		if(d > wolfd[!sp][u]) continue;
		// sp=0:다음 노드로 갈때 느림, sp=1:다음 노드로 갈때 빠름
		for(auto pr: adj[u]) {
			int nextd = d + (sp ? pr.second/2 : pr.second*2);
			if(nextd < wolfd[sp][pr.first]) {
				// wolfd[sp][i]를 늑대가 i에 (sp?빠른:느린) 속도로 도착했을 때에 최단거리로 정의
				wolfd[sp][pr.first] = nextd;
				pq.push({pr.first, nextd, sp});
				// pq안에 들어가는 sp도 pr.first까지 도착하는게 어떤 sp인지를 넣고, 이는 pop되고 `sp = !p.sp`에서 반전되어 다음 간선의 sp가 다르도록 함
			}
		}
	}
	int ans = 0;
	for(int i=2; i<=n; i++) {
		if(foxd[i] < min(wolfd[0][i], wolfd[1][i]))
			ans++;
	}
	cout << ans;
}
