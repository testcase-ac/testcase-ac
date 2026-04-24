#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1001;
int mark[MX], seen[MX];
vector<int> adj[MX], topo;
int dp[MX][MX];
void dfs(int i) {
	if(seen[i])
		return;
	seen[i] = 1;
	for(int a: adj[i])
		dfs(a);
	topo.push_back(i);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
	}
	int st, ed, k;
	cin >> st >> ed >> k;
	for(int i=0; i<k; i++) {
		int t;
		cin >> t;
		mark[t] = 1;
	}
	dfs(st);
	reverse(topo.begin(), topo.end());
	dp[st][mark[st] ? 1 : 0] = 1;
	for(int t: topo) {
		//printf("at t=%d\n", t);
		for(int i=0; i<=k; i++) {
			for(int s: adj[t]) {
				//printf("try visit %d\n", s);
				dp[s][i+(mark[s])] += dp[t][i]; 
			}
		}
	}
	cout << dp[ed][k];
}
