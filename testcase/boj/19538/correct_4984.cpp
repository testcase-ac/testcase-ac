#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 200001, INF = 0x3f3f3f3f;
vector<int> adj[MX];
int dist[MX], pushed[MX], cnt[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		int t;
		while((cin >> t), t != 0) {
			if(t > i) {
				adj[t].push_back(i);
				adj[i].push_back(t);
			}
		}
	}
	int m;
	cin >> m;
	memset(dist, 0x3f, sizeof dist);
	queue<int> que;
	for(int i=0; i<m; i++) {
		int t;
		cin >> t;
		//printf("t = %d is dist 0\n", t);
		dist[t] = 0;
		pushed[t] = 1;
		que.push(t);
	}
	int t = 1;
	while(que.size()) {
		int s = que.size();
		while(s--) {
			int q = que.front();
			que.pop();
			for(int a: adj[q]) {
				cnt[a]++;
				if(!pushed[a] && cnt[a] >= (adj[a].size()+1)/2) {
					//printf("pushed a=%d for time = %d\n", a, t);
					pushed[a] = 1;
					dist[a] = t;
					que.push(a);
				}
			}
		}
		t++;
	}
	for(int i=1; i<=n; i++) {
		if(dist[i] > INF)
			cout << "-1 ";
		else
			cout << dist[i] << ' ';
	}
}
