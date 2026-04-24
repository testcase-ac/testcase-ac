#include <bits/stdc++.h>
using namespace std;
char arr[1001][31];
int n, k;
vector<int> adj[1001];
int prv[1001], dist[1001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> k;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		for(int j=1; j<i; j++) {
			int cnt = 0;
			for(int x=0; x<k; x++)
				cnt += arr[i][x] != arr[j][x];
			if(cnt == 1) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}
	int s, f;
	cin >> s >> f;
	queue<int> que;
	que.push(s);
	memset(dist, 0x3f, sizeof dist);
	dist[s] = 0;
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		for(int v: adj[u]) {
			if(dist[v] > dist[u]+1) {
				dist[v] = dist[u]+1;
				prv[v] = u;
				que.push(v);
			}
		}
	}
	if(!prv[f])
		return !(cout << -1);
	int c = f;
	vector<int> v;
	while(c) {
		v.push_back(c);
		c = prv[c];
	}
	reverse(v.begin(), v.end());
	for(int i: v)
		cout << i << ' ';
}
