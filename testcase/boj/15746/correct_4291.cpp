#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
int len[MX], childcnt[MX], dp[MX], minans = LLONG_MAX;
vector<int> adj[MX];
void dfs(int i, int p) {
	for(int a: adj[i]) {
		if(a == p) continue;
		dfs(a, i);
		childcnt[i] += childcnt[a];
		dp[i] += dp[a]+childcnt[a]*len[a];
	}
}
void dfs2(int i, int p, int cur) {
	if(!(p && adj[i].size() == 1)) {
		//printf("at i=%d, cur=%d\n", i, cur);
		minans = min(minans, cur);
	}
	for(int a: adj[i]) {
		if(a == p) continue;
		dfs2(a, i, cur-(childcnt[a]*len[a])+(childcnt[1]-childcnt[a])*3);
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		string s;
		int m;
		cin >> s >> m;
		len[i] = s.size() + (m ? 1 : 0);
		if(!m)
			childcnt[i] = 1;
		for(int j=0; j<m; j++) {
			int t;
			cin >> t;
			adj[i].push_back(t);
			adj[t].push_back(i);
		}
	}
	dfs(1, 0);
	dfs2(1, 0, dp[1]);
	cout << minans;
}
