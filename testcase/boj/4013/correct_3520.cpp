#include <bits/stdc++.h>
using namespace std;
const int MX = 5e5+2;
vector<int> adj[MX], stk;
int num[MX], low[MX], val[MX], rest[MX], visiting[MX], dp[MX], nxt=1;
void dfs(int i) {
	num[i] = low[i] = nxt++;
	stk.push_back(i);
	visiting[i] = 1;
	for(int a: adj[i]) {
		if(!num[a]) {
			dfs(a);
		}
		if(visiting[a]) {
			//printf("update low of i=%d with edge %d.\n", i, a);
			low[i] = min(low[i], low[a]);
		}
	}
	//printf("finished i=%d. num=%d, low=%d\n", i, num[i], low[i]);
	if(num[i] == low[i]) {
		//printf("  is scc\n");
		int mxdp = 0, ok = 0, tsum = 0;
		vector<int> scc;
		while(1) {
			scc.push_back(stk.back());
			stk.pop_back();
			visiting[scc.back()] = 0;
			if(scc.back() == i) break;
		}
		for(int t: scc) {
			if(rest[t])
				ok = 1;
			tsum += val[t];
			for(int a: adj[t]) {
				mxdp = max(mxdp, dp[a]);
				if(rest[a])
					ok = 1;
			}
		}
		//printf("  ok=%d, tsum=%d, mxdp=%d\n", ok, tsum, mxdp);
		if(ok)
			mxdp += tsum;
		for(int t: scc) {
			rest[t] = ok;
			dp[t] = mxdp;
		}
		//printf("  dp all set to %d\n", dp[i]);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
	for(int i=1; i<=n; i++) {
		cin >> val[i];
	}
	int s, p;
	cin >> s >> p;
	for(int i=0; i<p; i++) {
		int t;
		cin >> t;
		rest[t] = 1;
	}
	dfs(s);
	cout << dp[s];
}
