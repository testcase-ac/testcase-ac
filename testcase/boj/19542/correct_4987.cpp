#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 100004;
vector<int> adj[MX];
int depth[MX], mxd[MX], D;
void dfs1(int i, int p) {
	mxd[i] = depth[i];
	for(int u: adj[i]) {
		if(u == p)
			continue;
		depth[u] = depth[i]+1;
		dfs1(u, i);
		mxd[i] = max(mxd[u], mxd[i]);
	}
}
int ans = 0;
void dfs(int i, int p) {
	for(int u: adj[i]) {
		if(u == p) continue;
		if(mxd[u] <= depth[i]+D) continue;
		//printf("from %d to %d\n", i, u);
		ans++;
		dfs(u, i);
	}
	//printf("return from %d\n", i);
	ans++;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, s;
	cin >> n >> s >> D;
	for(int i=0; i<n-1; i++) {
		int x, y;
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs1(s, -1);
	dfs(s, -1);
	cout << ans-1;
}
